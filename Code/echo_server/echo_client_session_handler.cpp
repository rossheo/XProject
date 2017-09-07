#include "stdafx.h"
#include "echo_client_session.h"

#include "p_echo_client_server.h"
#include "p_echo_server_client.h"

namespace XP
{
SESSION_UTIL(EchoClientSession, g_SessionManager)

DECLARE_HANDLER(EchoClientSession, PC2S_Chat);

IMPLEMENT_INITIALIZE(EchoClientSession)
{
    REGISTER_HANDLER(PC2S_Chat);
}

IMPLEMENT_HANDLER(EchoClientSession, PC2S_Chat)
{
    const auto& remoteEndpoint = session.GetSocket().remote_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "{}, Message:{}",
        remoteEndpoint, FromUTF8(packet.message()));

    PS2C_Chat out;
    out.set_message(packet.message());
    //session.SendPacket(out);
    session.BroadcastPacket(out);
}

} // namespace XP
