#pragma once
#include "packet_handler_manager.h"
#include "session_manager.h"
#include "unit_lock.h"

namespace XP
{

template <typename TSession>
class Session : public std::enable_shared_from_this<TSession>
{
public:
    static PacketHandlerManager<TSession> _s_packetHandlerManager;

public:
    explicit Session(boost::asio::io_service& ioservice,
        SessionManager<TSession>* pSessionManager = nullptr);
    virtual ~Session();

protected:
    virtual void Shutdown(
        boost::asio::socket_base::shutdown_type shutdownType =
        boost::asio::socket_base::shutdown_type::shutdown_both) noexcept;

public:
    void OnConnect();
    void OnDisconnect(boost::asio::socket_base::shutdown_type shutdownType);

    bool PostReceive();
    void PostWrite();

    template <typename T>
    bool SendPacket(const T& packet);

    template <typename T>
    bool BroadcastPacket(const T& packet);

    boost::asio::ip::tcp::socket& GetSocket() { return _socket; }

    bool HaveRemoteEndPoint() const;
    Uuid GetUuid() const;

protected:
    boost::asio::ip::tcp::socket _socket;
    Uuid _uuid;
    SessionManager<TSession>* _pSessionManager;

    PacketBuffer _recvBuffer;
    PacketBuffer _sendBuffer;

    SlimRWLock _lock;
};

template <typename TSession>
Session<TSession>::Session(boost::asio::io_service& ioservice,
    SessionManager<TSession>* pSessionManager /*= nullptr*/)
    : _socket(ioservice)
    , _pSessionManager(pSessionManager)
{
    UnitThreadLocalStorage::Initialize();
}

template <typename TSession>
Session<TSession>::~Session()
{
    Shutdown();
    UnitThreadLocalStorage::Release();
}

namespace
{
std::wstring GetShutdownTypeString(boost::asio::socket_base::shutdown_type shutdownType)
{
    switch (shutdownType)
    {
    case boost::asio::socket_base::shutdown_type::shutdown_send:
        return TEXT("shutdown_send");
    case boost::asio::socket_base::shutdown_type::shutdown_receive:
        return TEXT("shutdown_receive");
    case boost::asio::socket_base::shutdown_type::shutdown_both:
        return TEXT("shutdown_both");
    }

    return TEXT("shutdown_unknown");
}
} // nonamed namespace

template <typename TSession>
void Session<TSession>::Shutdown(
    boost::asio::socket_base::shutdown_type shutdownType) noexcept
{
    if (!_socket.is_open())
        return;

    try
    {
        OnDisconnect(shutdownType);
        _socket.shutdown(shutdownType);
        _socket.close();
    }
    catch (const boost::system::error_code& errorCode)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "Fail to close socket. {}", errorCode);
    }
    catch (const std::exception& ex)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "Fail to close socket. {}", ex);
    }
}

template <typename TSession>
void Session<TSession>::OnConnect()
{
    const boost::asio::ip::tcp::endpoint& remoteEndpoint = _socket.remote_endpoint();

    LOG_INFO(LOG_FILTER_CONNECTION, "Session connected."
        " {}, {}", remoteEndpoint, _uuid);
}

template <typename TSession>
void Session<TSession>::OnDisconnect(boost::asio::socket_base::shutdown_type shutdownType)
{
    const boost::asio::ip::tcp::endpoint& remoteEndpoint = _socket.remote_endpoint();

    LOG_INFO(LOG_FILTER_CONNECTION, "Session disconnected.({})."
        " {}, {}",
        GetShutdownTypeString(shutdownType), remoteEndpoint, _uuid);
}

template <typename TSession>
bool Session<TSession>::PostReceive()
{
    if (!_socket.is_open())
    {
        LOG_ERROR(LOG_FILTER_CONNECTION, "Fail to PostReceive. Session is disconnected.");
        return false;
    }

    if (_recvBuffer.IsNotEnoughBuffer())
    {
        _recvBuffer.ReArrange();
    }

    auto self(shared_from_this());
    _socket.async_read_some(
        boost::asio::buffer(_recvBuffer.GetMutableBuffer(),
            static_cast<std::size_t>(_recvBuffer.GetRemainSize())),
        [this, selfMoved = std::move(self)]
    (const boost::system::error_code& errorCode, std::size_t bytes_transferred)
    {
        if (!_socket.is_open())
        {
            LOG_ERROR(LOG_FILTER_CONNECTION, "Fail to PostReceive."
                " Session is disconnected.");
            return;
        }

        const auto& remoteEndPoint = _socket.remote_endpoint();

        if (errorCode || (bytes_transferred == 0))
        {
            boost::asio::socket_base::shutdown_type shutdownType =
                boost::asio::socket_base::shutdown_type::shutdown_receive;

            if (errorCode == boost::asio::error::eof ||
                errorCode == boost::asio::error::connection_reset)
            {
                shutdownType =
                    boost::asio::socket_base::shutdown_type::shutdown_both;

                LOG_INFO(LOG_FILTER_CONNECTION, "Disconnected. {}", remoteEndPoint);
            }
            else if (errorCode == boost::asio::error::connection_aborted)
            {
                LOG_INFO(LOG_FILTER_CONNECTION, "Connection aborted. {}", remoteEndPoint);
            }
            else if (bytes_transferred == 0)
            {
                LOG_INFO(LOG_FILTER_CONNECTION, "Disconnected. 0 bytes transferred."
                " {}", remoteEndPoint);
            }
            else
            {
                LOG_ERROR(LOG_FILTER_CONNECTION, "Connection receive error."
                    " {}, {}, {}",
                    errorCode, remoteEndPoint, _uuid);
            }

            Shutdown(shutdownType);
            return;
        }

        if (!_recvBuffer.AppendWriteSize(static_cast<uint16>(bytes_transferred)))
        {
            LOG_ERROR(LOG_FILTER_CONNECTION, "Receive buffer error."
                " recvBuffer remain size: {}, bytes_transferred: {}",
                _recvBuffer.GetRemainSize(), bytes_transferred);

            Shutdown(boost::asio::socket_base::shutdown_type::shutdown_receive);
            return;
        }

        while (_recvBuffer.IsAbleToGetPacket())
        {
            if (!_s_packetHandlerManager.Handle(
                static_cast<TSession&>(*this), _recvBuffer))
            {
                LOG_ERROR(LOG_FILTER_CONNECTION, "Receive Handler failed."
                    " packetNumber: {}",
                    _recvBuffer.GetPacketNo());

                Shutdown(boost::asio::socket_base::shutdown_type::shutdown_receive);
                return;
            }
        }

        PostReceive();
    });

    return true;
}

template <typename TSession>
void Session<TSession>::PostWrite()
{
    if (!_socket.is_open())
    {
        LOG_ERROR(LOG_FILTER_CONNECTION, "Fail to PostWrite. socket is closed.");
        return;
    }

    LOCK_R(_lock);

    if (_sendBuffer.IsEmptyData())
        return;

    auto self(shared_from_this());
    boost::asio::async_write(_socket,
        boost::asio::buffer(_sendBuffer.GetBuffer(), _sendBuffer.GetBufferSize()),
        [this, selfMoved = std::move(self)](
            const boost::system::error_code& errorCode, std::size_t bytes_transferred)
    {
        if (!_socket.is_open())
        {
            LOG_ERROR(LOG_FILTER_CONNECTION, "Fail to PostWrite."
                " Session is disconnected.");
            return;
        }

        {
            LOCK_W(_lock);

            const auto& remoteEndPoint = _socket.remote_endpoint();

            if (errorCode || (bytes_transferred == 0))
            {
                boost::asio::socket_base::shutdown_type shutdownType =
                    boost::asio::socket_base::shutdown_type::shutdown_send;

                if (errorCode == boost::asio::error::eof ||
                    errorCode == boost::asio::error::connection_reset)
                {
                    shutdownType = boost::asio::socket_base::shutdown_type::shutdown_both;

                    LOG_INFO(LOG_FILTER_CONNECTION, "Disconnected. {}", remoteEndPoint);
                }
                else if (errorCode == boost::asio::error::connection_aborted)
                {
                    LOG_INFO(LOG_FILTER_CONNECTION, "Connection aborted. {}", remoteEndPoint);
                }
                else if (bytes_transferred == 0)
                {
                    LOG_INFO(LOG_FILTER_CONNECTION, "Disconnected. 0 bytes transferred. {}",
                        remoteEndPoint);
                }
                else
                {
                    LOG_ERROR(LOG_FILTER_CONNECTION, "Connection send error. {}, {}",
                        errorCode, remoteEndPoint);
                }

                Shutdown(shutdownType);
                return;
            }

            _sendBuffer.TruncateBuffer(static_cast<uint16>(bytes_transferred));

            if (_sendBuffer.IsEmptyData())
            {
                _sendBuffer.ReArrange();
                return;
            }
        }

        PostWrite();
    });
}

template <typename TSession>
template <typename T>
bool Session<TSession>::SendPacket(const T& packet)
{
    bool callPostWrite = false;

    {
        LOCK_W(_lock);

        if (_sendBuffer.IsEmptyData())
            callPostWrite = true;

        if (!_sendBuffer.AppendPacket(packet))
        {
            LOG_ERROR(LOG_FILTER_PACKET_BUFFER, "Fail to SetPacket().");
            return false;
        }
    }

    if (callPostWrite)
        PostWrite();

    return true;
}

template <typename TSession>
template <typename T>
bool Session<TSession>::BroadcastPacket(const T& packet)
{
    if (!_pSessionManager)
        return false;

    _pSessionManager->Visitor(
        [&packet](std::shared_ptr<TSession>&& spSession)
    {
        spSession->SendPacket(packet);
    });

    return true;
}

template <typename TSession>
bool Session<TSession>::HaveRemoteEndPoint() const
{
    boost::system::error_code errorCode;
    boost::asio::ip::tcp::endpoint endPoint = _socket.remote_endpoint(errorCode);
    if (errorCode)
        return false;

    return true;
}

template <typename TSession>
Uuid Session<TSession>::GetUuid() const
{
    return _uuid;
}

} // namespace XP
