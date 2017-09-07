#pragma once
#include "session.h"
#include "p_prototype_client_server.h"

namespace XP
{

class PrototypeServerSession : public Session<PrototypeServerSession>
{
public:
    explicit PrototypeServerSession(boost::asio::io_service& ioservice)
        : Session(ioservice)
    {
    };

    virtual ~PrototypeServerSession()
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
                " {}, {}",
                errorCode, endpoint);
            return;
        }

        LOG_INFO(LOG_FILTER_CONNECTION, "Connected. {}", endpoint);
    }

    void SendMessage(const std::wstring& message)
    {
        PC2S_Chat out;
        out.set_message(ToUTF8(message));
        SendPacket(out);
    }

    void SendAuth(const std::wstring& id, const std::wstring& password)
    {
        PC2S_Auth out;
        out.set_id(ToUTF8(id));
        out.set_password(ToUTF8(password));
        SendPacket(out);
    }
};

} // namespace XP
