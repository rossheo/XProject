#include "stdafx.h"
#include "server_session.h"

#include "p_client_server.h"
#include "p_server_client.h"

namespace XP
{

DECLARE_HANDLER(ServerSession, PS2C_Chat);

IMPLEMENT_INITIALIZE(ServerSession)
{
    REGISTER_HANDLER(PS2C_Chat);
}

IMPLEMENT_HANDLER(ServerSession, PS2C_Chat)
{
    LOG_INFO(LOG_FILTER_CLIENT, "FromServer: {}", packet.message());

    if (boost::starts_with(packet.message(), "loop"))
    {
        PC2S_Chat out;
        out.set_message(packet.message());
        session.SendPacket(packet);
    }

    return true;
}

} // namespace XP