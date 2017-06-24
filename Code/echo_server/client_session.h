#pragma once
#include "session.h"

namespace XP
{

class ClientSession : public Session<ClientSession>
{
public:
    explicit ClientSession(boost::asio::io_service& ioservice,
        SessionManager<ClientSession>* pSessionManager);
    virtual ~ClientSession();

    void OnConnect();
    void OnDisconnect(boost::asio::socket_base::shutdown_type shutdownType);
};

} // namespace XP
