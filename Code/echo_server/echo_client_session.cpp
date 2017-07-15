#include "stdafx.h"
#include "echo_client_session.h"
#include "echo_server_app.h"

namespace XP
{

EchoClientSession::EchoClientSession(boost::asio::io_service& ioservice,
    SessionManager<EchoClientSession>* pSessionManager)
    : Session(ioservice, pSessionManager)
{
}

EchoClientSession::~EchoClientSession()
{
    if (_pSessionManager)
        _pSessionManager->RemoveSession(this);
}

void EchoClientSession::OnConnect()
{
    __super::OnConnect();
}

void EchoClientSession::OnDisconnect(boost::asio::socket_base::shutdown_type shutdownType)
{
    __super::OnDisconnect(shutdownType);
}

} // namespace XP
