#pragma once

namespace XP
{

template <typename TSession>
class SessionManager
{
public:
    explicit SessionManager();
    ~SessionManager();

public:
    std::shared_ptr<TSession> CreateSession(boost::asio::io_service& ioservice);
    void RemoveSession(const TSession* pSession);

private:
    void AddSession(std::weak_ptr<TSession>&& wpSession);

private:
    std::vector<std::weak_ptr<TSession>> _sessions;
    SlimRWLock _lock;
};

template <typename TSession>
SessionManager<TSession>::SessionManager()
{
    const std::size_t session_reserve = 3000;
    _sessions.reserve(session_reserve);
}

template <typename TSession>
SessionManager<TSession>::~SessionManager()
{
}

template <typename TSession>
std::shared_ptr<TSession> SessionManager<TSession>::CreateSession(
    boost::asio::io_service& ioservice)
{
    if (auto spSession = std::make_shared<TSession>(ioservice))
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

} // namespace XP
