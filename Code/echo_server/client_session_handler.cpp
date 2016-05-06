#include "stdafx.h"
#include "client_session.h"

#include "p_client_server.h"
#include "p_server_client.h"

namespace XP
{

DECLARE_HANDLER(ClientSession, PC2S_Chat);

IMPLEMENT_INITIALIZE(ClientSession)
{
    REGISTER_HANDLER(PC2S_Chat);
}

IMPLEMENT_HANDLER(ClientSession, PC2S_Chat)
{
    const auto& remoteEndpoint = session.GetSocket().remote_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "IP:{}, PORT:{}, Message:{}",
        remoteEndpoint.address().to_string(),
        remoteEndpoint.port(),
        packet.message());

    PS2C_Chat out;
    out.set_message(packet.message());
    session.SendPacket(out);
    return true;
}

} // namespace XP
