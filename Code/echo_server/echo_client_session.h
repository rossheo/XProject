#pragma once
#include "session.h"

namespace XP
{

class EchoClientSession : public Session<EchoClientSession>
{
public:
    explicit EchoClientSession(boost::asio::io_service& ioservice,
        SessionManager<EchoClientSession>* pSessionManager);
    virtual ~EchoClientSession();

    void OnConnect();
    void OnDisconnect(boost::asio::socket_base::shutdown_type shutdownType);
};

} // namespace XP
