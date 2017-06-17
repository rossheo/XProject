#include "stdafx.h"
#include "client_session.h"

#include "p_client_server.h"
#include "p_server_client.h"

namespace XP
{

DECLARE_HANDLER(ClientSession, PC2S_Chat);
DECLARE_HANDLER(ClientSession, PC2S_Auth);

IMPLEMENT_INITIALIZE(ClientSession)
{
    REGISTER_HANDLER(PC2S_Chat);
    REGISTER_HANDLER(PC2S_Auth);
}

IMPLEMENT_HANDLER(ClientSession, PC2S_Chat)
{
    const auto& remoteEndpoint = session.GetSocket().remote_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "IP:{}, PORT:{}, Message:{}",
        remoteEndpoint.address().to_string(),
        remoteEndpoint.port(),
        FromUTF8(packet.message()));

    PS2C_Chat out;
    out.set_message(packet.message());
    session.SendPacket(out);
    return true;
}

IMPLEMENT_HANDLER(ClientSession, PC2S_Auth)
{
    const auto& remoteEndpoint = session.GetSocket().remote_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "IP:{}, PORT:{}, ID:{}, PW:{}",
        remoteEndpoint.address().to_string(),
        remoteEndpoint.port(),
        FromUTF8(packet.id()),
        FromUTF8(packet.password()));

    PS2C_Auth out;
    out.set_auth_result("auth_success");
    session.SendPacket(out);
    return true;
}

} // namespace XP
