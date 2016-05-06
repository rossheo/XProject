#pragma once

#include <google/protobuf/message_lite.h>
#include "packet_buffer.h"

// Packet 정의
#define DECLARE_HANDLER(TSession, TProtoBuf)\
template<typename TSession, typename TProtoBuf>\
class PacketHandler;\
template <>\
class PacketHandler<TSession, TProtoBuf>\
{\
public:\
    bool operator()(TSession& session, TProtoBuf&& packet);\
};

// Static 함수 초기화 선언
#define IMPLEMENT_INITIALIZE(TSession)\
TSession::TPacketHandlerManager Session<TSession>::_s_packet_handler_manager;\
static void Initialize(TSession::TPacketHandlerManager& packetHandlerManager)

// 패킷 함수 핸들러에 등록
#define REGISTER_HANDLER(TProtoBuf)\
packetHandlerManager.Register<TProtoBuf>(TProtoBuf::PROTOCOL_NUMBER)

// 패킷 핸들러 구현
#define IMPLEMENT_HANDLER(TSession, TProtoBuf)\
bool PacketHandler<TSession, TProtoBuf>::operator()(TSession& session, TProtoBuf&& packet)

namespace XP
{

template<typename TSession>
class PacketFunctorBase
{
public:
    explicit PacketFunctorBase() {};
    virtual ~PacketFunctorBase() {};

    virtual bool Handle(TSession& session, PacketBuffer& packetBuffer) const = 0;
};

template<typename TSession, typename TProtoBuf>
class PacketFunctor : PacketFunctorBase<TSession>
{
public:
    explicit PacketFunctor() {};
    virtual ~PacketFunctor() {};

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

        return PacketHandler<TSession, TProtoBuf>()(session, std::move(protobuf));
    }
};

template<typename TSession>
class PacketHandlerManager
{
public:
    explicit PacketHandlerManager() 
    {
        ClearPacketFunctors();
        Initialize(*this);
    };

    ~PacketHandlerManager() 
    {
        ClearPacketFunctors();
    };

    template<class TProtoBuf>
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
