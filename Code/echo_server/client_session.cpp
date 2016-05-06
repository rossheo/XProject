#include "stdafx.h"
#include "client_session.h"
#include "echo_server_app.h"

namespace XP
{
ClientSession::ClientSession(boost::asio::io_service& ioservice)
    : Session(ioservice)
{
}

ClientSession::~ClientSession()
{
    g_EchoServerApp.RemoveSession(this);
}

} // namespace XP
