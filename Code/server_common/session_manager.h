#pragma once
#include "player_unit.h"

namespace XP
{

template <typename TSession>
class SessionManager
{
public:
    explicit SessionManager();
    ~SessionManager();

public:
    struct SessionTag
    {
        SessionTag(const TSession* pSession_, const UnitId& unitId_, const PlayerUnit* pUnit_)
            : pSession(pSession_)
            , unitId(unitId_)
            , pUnit(pUnit_)
        {
        }

        const TSession* pSession;
        UnitId unitId;
        const PlayerUnit* pUnit;
    };

    struct tagSession {};
    struct tagUnitId {};
    struct tagUnit {};

    typedef boost::multi_index::multi_index_container<
        SessionTag,
        boost::multi_index::indexed_by
        <
        boost::multi_index::hashed_unique<
        boost::multi_index::tag<tagSession>,
        boost::multi_index::member<SessionTag, const TSession*, &SessionTag::pSession>
        >,
        boost::multi_index::hashed_unique<
        boost::multi_index::tag<tagUnitId>,
        boost::multi_index::member<SessionTag, UnitId, &SessionTag::unitId>
        >,
        boost::multi_index::hashed_unique<
        boost::multi_index::tag<tagUnit>,
        boost::multi_index::member<SessionTag, const PlayerUnit*, &SessionTag::pUnit>
        >
        >
    > SessionMultiIndex;

public:
    template <typename Fn>
    void Visitor(const Fn& functor);

    std::shared_ptr<TSession> CreateSession(boost::asio::io_service& ioservice);
    void RemoveSession(const TSession* pSession);

    void AssociateUnitWithSession(const TSession& session, const PlayerUnit& unit);
    bool Get(const TSession* pSession, UnitId& unitId) const;
    bool Get(const TSession* pSession, PlayerUnit* pUnit) const;
    bool Get(const UnitId& unitId, TSession* pSession) const;
    bool Get(const UnitId& unitId, PlayerUnit* pUnit) const;
    bool Get(const PlayerUnit* pUnit, TSession* pSession) const;
    bool Get(const PlayerUnit* pUnit, UnitId& unitId) const;

private:
    void AddSession(std::weak_ptr<TSession>&& wpSession);
    void RemoveSessionMultiIndex(const TSession* pSession);

private:
    std::vector<std::weak_ptr<TSession>> _sessions;
    SessionMultiIndex _sessionMultiIndex;
    mutable SlimRWLock _lock;
};

template <typename TSession>
SessionManager<TSession>::SessionManager()
{
    const std::size_t session_reserve = 5000;
    _sessions.reserve(session_reserve);
}

template <typename TSession>
SessionManager<TSession>::~SessionManager()
{
}

template <typename TSession>
template <typename Fn>
void SessionManager<TSession>::Visitor(const Fn& functor)
{
    LOCK_W(_lock);

    for (const auto& wpSession : _sessions)
    {
        auto spSession = wpSession.lock();
        if (!spSession || !spSession->HaveRemoteEndPoint())
            continue;

        functor(std::move(spSession));
    }
}

template <typename TSession>
std::shared_ptr<TSession> SessionManager<TSession>::CreateSession(
    boost::asio::io_service& ioservice)
{
    if (auto spSession = std::make_shared<TSession>(ioservice, this))
    {
        std::weak_ptr<TSession> wpSession(spSession);
        AddSession(std::move(wpSession));
        return spSession;
    }

    LOG_FATAL(LOG_FILTER_SERVER, "Fail to create session.");
    return nullptr;
}

template <typename TSession>
void SessionManager<TSession>::RemoveSession(const TSession* pSession)
{
    if (!pSession)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "pSession is nullptr.");
        return;
    }

    {
        LOCK_W(_lock);

        RemoveSessionMultiIndex(pSession);

        {
            auto it = std::remove_if(_sessions.begin(), _sessions.end(),
                [](const auto& elem)
            {
                return elem.expired();
            });

            _sessions.erase(it, _sessions.end());
        }

        {
            auto it = std::find_if(_sessions.begin(), _sessions.end(),
                [pSession](const auto& elem)
            {
                return pSession == elem.lock().get();
            });

            if (it != _sessions.end())
            {
                _sessions.erase(it);
            }
        }
    }
}

template <typename TSession>
void SessionManager<TSession>::AddSession(std::weak_ptr<TSession>&& wpSession)
{
    if (wpSession.expired())
    {
        LOG_ERROR(LOG_FILTER_SERVER, "wpSession is expired.");
        return;
    }

    {
        LOCK_W(_lock);

        auto it = std::find_if(_sessions.cbegin(), _sessions.cend(),
            [&wpSession](const auto& elem)
        {
            return wpSession.lock() == elem.lock();
        });

        if (it != _sessions.cend())
        {
            LOG_ERROR(LOG_FILTER_SERVER, "Fail to add session.");
            return;
        }

        _sessions.push_back(std::move(wpSession));
    }
}

template <typename TSession>
void SessionManager<TSession>::RemoveSessionMultiIndex(const TSession* pSession)
{
    if (!pSession)
        return;

    auto& session_index = _sessionMultiIndex.get<tagSession>();
    auto it = session_index.find(pSession);
    if (it != session_index.end())
    {
        session_index.erase(it);
    }
}

template <typename TSession>
void SessionManager<TSession>::AssociateUnitWithSession(
    const TSession& session, const PlayerUnit& unit)
{
    LOCK_W(_lock);
    _sessionMultiIndex.insert({ &session, unit.GetUnitId(), &unit });
}


template <typename TSession>
bool SessionManager<TSession>::Get(const TSession* pSession, UnitId& unitId) const
{
    if (!pSession)
    {
        unitId = UnitId::INVALID:
        return false;
    }

    LOCK_R(_lock);

    auto& session_index = _sessionMultiIndex.get<tagSession>();
    auto it = session_index.find(pSession);
    if (it != session_index.end())
    {
        unitId = (*it).unitId;
        return true;
    }

    unitId = UnitId::INVALID:
    return false;
}

template <typename TSession>
bool SessionManager<TSession>::Get(const TSession* pSession, PlayerUnit* pUnit) const
{
    if (!pSession)
    {
        pUnit = nullptr;
        return false;
    }

    LOCK_R(_lock);

    auto& session_index = _sessionMultiIndex.get<tagSession>();
    auto it = session_index.find(pSession);
    if (it != session_index.end())
    {
        pUnit = const_cast<PlayerUnit*>((*it).pUnit);
        return true;
    }

    pUnit = nullptr;
    return false;
}

template <typename TSession>
bool SessionManager<TSession>::Get(const UnitId& unitId, TSession* pSession) const
{
    if (unitId.IsInvalid())
    {
        pSession = nullptr;
        return false;
    }

    LOCK_R(_lock);

    auto& unitId_index = _sessionMultiIndex.get<tagUnitId>();
    auto it = unitId_index.find(unitId);
    if (it != unitId_index.end())
    {
        pSession = (*it).pSession;
        return true;
    }

    pSession = nullptr;
    return false;
}

template <typename TSession>
bool SessionManager<TSession>::Get(const UnitId& unitId, PlayerUnit* pUnit) const
{
    if (unitId.IsInvalid())
    {
        pUnit = nullptr;
        return false;
    }

    LOCK_R(_lock);

    auto& unitId_index = _sessionMultiIndex.get<tagUnitId>();
    auto it = unitId_index.find(unitId);
    if (it != unitId_index.end())
    {
        pUnit = (*it).pUnit;
        return true;
    }

    pUnit = nullptr;
    return false;
}

template <typename TSession>
bool SessionManager<TSession>::Get(const PlayerUnit* pUnit, TSession* pSession) const
{
    if (!pUnit)
    {
        pSession = nullptr;
        return false;
    }

    LOCK_R(_lock);

    auto& unit_index = _sessionMultiIndex.get<tagUnit>();
    auto it = unit_index.find(pUnit);
    if (it != unit_index.end())
    {
        pSession = (*it).pSession;
        return true;
    }

    pSession = nullptr;
    return false;
}

template <typename TSession>
bool SessionManager<TSession>::Get(const PlayerUnit* pUnit, UnitId& unitId) const
{
    if (!pUnit)
    {
        unitId = unitId::INVALID;
        return false;
    }

    LOCK_R(_lock);

    auto& unit_index = _sessionMultiIndex.get<tagUnit>();
    auto it = unit_index.find(pUnit);
    if (it != unit_index.end())
    {
        unitId = (*it).unitId;
        return true;
    }

    unitId = unitId::INVALID;
    return false;
}

} // namespace XP
