#pragma once

#include "packet_buffer.h"

// Session Util 정의
#define SESSION_UTIL(TSession, SessionManagerInstance)\
template <typename TPacket>\
void SendPacket(const UnitId& unitId, TPacket&& packet)\
{\
    TSession* pSession;\
    if (!SessionManagerInstance.Get(unitId, pSession))\
        return;\
    pSession->SendPacket(packet);\
}\
template <typename TPacket>\
void Broadcast(const std::set<UnitId>& unitIds, TPacket&& packet)\
{\
    for (const auto& unitId : unitIds)\
    {\
        SendPacket(unitId, packet);\
    }\
}

// Packet 정의
#define DECLARE_HANDLER(TSession, TProtoBuf)\
template<typename TSession, typename TProtoBuf>\
class PacketHandler;\
template <>\
class PacketHandler<TSession, TProtoBuf>\
{\
public:\
    void operator()(TSession& session, TProtoBuf&& packet);\
};

// Static 함수 초기화 선언
#define IMPLEMENT_INITIALIZE(TSession)\
template <>\
PacketHandlerManager<TSession> Session<TSession>::_s_packetHandlerManager;\
static void Initialize(PacketHandlerManager<TSession>& packetHandlerManager)

// 패킷 함수 핸들러에 등록
#define REGISTER_HANDLER(TProtoBuf)\
packetHandlerManager.Register<TProtoBuf>(TProtoBuf::PROTOCOL_NUMBER)

// 패킷 핸들러 구현
#define IMPLEMENT_HANDLER(TSession, TProtoBuf)\
void PacketHandler<TSession, TProtoBuf>::operator()(TSession& session, TProtoBuf&& packet)

namespace XP
{

template<typename TSession>
class PacketFunctorBase
{
public:
    explicit PacketFunctorBase() {}
    virtual ~PacketFunctorBase() {}

    virtual bool Handle(TSession& session, PacketBuffer& packetBuffer) const = 0;
};

template<typename TSession, typename TProtoBuf>
class PacketFunctor : PacketFunctorBase<TSession>
{
public:
    explicit PacketFunctor() {}
    virtual ~PacketFunctor() {}

    virtual bool Handle(TSession& session, PacketBuffer& packetBuffer) const override
    {
        TProtoBuf protobuf;
        if (!protobuf.ParseFromArray(
            packetBuffer.GetPayloadBuffer(), packetBuffer.GetPayloadBufferSize()))
        {
            LOG_ERROR(LOG_FILTER_PACKET_HANDLER, "PacketParse error.");
            return false;
        }

        packetBuffer.ConsumePacket();

        PacketHandler<TSession, TProtoBuf>()(session, std::move(protobuf));
        return true;
    }
};

template <typename TSession>
class PacketHandlerManager
{
public:
    explicit PacketHandlerManager() 
    {
        ClearPacketFunctors();
        Initialize(*this);
    }

    ~PacketHandlerManager() 
    {
        ClearPacketFunctors();
    }

    template <typename TProtoBuf>
    bool Register(uint16 protocolNumber)
    {
        if (protocolNumber > _packetFunctors.size())
        {
            LOG_ERROR(LOG_FILTER_PACKET_HANDLER, "ProtocolNumber is out of range."
                " protocolNumber: {}",
                protocolNumber);
            return false;
        }

        if (_packetFunctors[protocolNumber])
        {
            LOG_ERROR(LOG_FILTER_PACKET_HANDLER, "Already registered protocol."
                " protocolNumber: {}",
                protocolNumber);
            return false;
        }

        PacketFunctorBase<TSession>* pPacketFunctor =
            reinterpret_cast<PacketFunctorBase<TSession>*>(
            new PacketFunctor<TSession, TProtoBuf>());

        _packetFunctors[protocolNumber].reset(pPacketFunctor);
        return true;
    }

    bool Handle(TSession& session, PacketBuffer& packetBuffer)
    {
        const uint16 packetNo = packetBuffer.GetPacketNo();

        PacketFunctorBase<TSession>* pFnPacketHandler = _packetFunctors[packetNo].get();
        if (!pFnPacketHandler)
        {
            LOG_ERROR(LOG_FILTER_PACKET_HANDLER, "PacketHandler is not exist."
                " packetNo: {}",
                packetNo);
            return false;
        }

        return pFnPacketHandler->Handle(session, packetBuffer);
    }

    void ClearPacketFunctors() noexcept
    {
        for (auto& functor : _packetFunctors)
        {
            functor.reset();
        }
    }

private:
    std::array<
        std::unique_ptr<PacketFunctorBase<TSession>>,
        boost::integer_traits<uint16>::max()
    > _packetFunctors;
};

} // namespace XP
