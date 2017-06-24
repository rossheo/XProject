#include "stdafx.h"
#include "prototype_client_session.h"
#include "prototype_server_app.h"

namespace XP
{

PrototypeClientSession::PrototypeClientSession(boost::asio::io_service& ioservice,
    SessionManager<PrototypeClientSession>* pSessionManager)
    : Session(ioservice, pSessionManager)
{
}

PrototypeClientSession::~PrototypeClientSession()
{
    if (_pSessionManager)
        _pSessionManager->RemoveSession(this);
}

} // namespace XP
