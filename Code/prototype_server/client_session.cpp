#include "stdafx.h"
#include "client_session.h"
#include "prototype_server_app.h"

namespace XP
{
ClientSession::ClientSession(boost::asio::io_service& ioservice)
    : Session(ioservice)
{
}

ClientSession::~ClientSession()
{
    g_PrototypeServerApp.RemoveSession(this);
}

} // namespace XP
