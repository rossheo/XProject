#include "stdafx.h"
#include "client_session.h"
#include "echo_server_app.h"

namespace XP
{

ClientSession::ClientSession(boost::asio::io_service& ioservice,
    SessionManager<ClientSession>* pSessionManager)
    : Session(ioservice, pSessionManager)
{
}

ClientSession::~ClientSession()
{
    if (_pSessionManager)
        _pSessionManager->RemoveSession(this);
}

} // namespace XP
