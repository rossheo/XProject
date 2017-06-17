#include "stdafx.h"
#include "prototype_client_session.h"
#include "prototype_server_app.h"

namespace XP
{
PrototypeClientSession::PrototypeClientSession(boost::asio::io_service& ioservice)
    : Session(ioservice)
{
}

PrototypeClientSession::~PrototypeClientSession()
{
    g_PrototypeServerApp.RemoveSession(this);
}

} // namespace XP
