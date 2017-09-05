#pragma once
#include "session.h"
#include "p_echo_client_server.h"

namespace XP
{

class ServerSession : public Session<ServerSession>
{
public:
    explicit ServerSession(boost::asio::io_service& ioservice)
        : Session(ioservice)
    {
    };

    virtual ~ServerSession()
    {
    };

public:
    void Connect(const boost::asio::ip::tcp::endpoint& endpoint)
    {
        boost::system::error_code errorCode;
        _socket.connect(endpoint, errorCode);

        if (errorCode)
        {
            LOG_ERROR(LOG_FILTER_CONNECTION, "Fail to connect."
                " {}, ip: {}, port: {}",
                errorCode, endpoint.address().to_string(), endpoint.port());
            return;
        }

        LOG_INFO(LOG_FILTER_CONNECTION, "Connected. ip: {}, port: {}",
            endpoint.address().to_string(), endpoint.port());
    }

    void SendMessage(const std::wstring& message)
    {
        PC2S_Chat out;
        out.set_message(ToUTF8(message));
        SendPacket(out);
    }
};

} // namespace XP
