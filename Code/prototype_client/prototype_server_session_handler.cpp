#include "stdafx.h"
#include "prototype_server_session.h"

#include "p_client_server.h"
#include "p_server_client.h"

namespace XP
{

DECLARE_HANDLER(PrototypeServerSession, PS2C_Chat);
DECLARE_HANDLER(PrototypeServerSession, PS2C_Auth);

IMPLEMENT_INITIALIZE(PrototypeServerSession)
{
    REGISTER_HANDLER(PS2C_Chat);
    REGISTER_HANDLER(PS2C_Auth);
}

IMPLEMENT_HANDLER(PrototypeServerSession, PS2C_Chat)
{
    std::wstring message(FromUTF8(packet.message()));

    LOG_INFO(LOG_FILTER_CLIENT, "FromServer(Message): {}", message);

    if (boost::starts_with(message, TEXT("loop")))
    {
        PC2S_Chat out;
        out.set_message(packet.message());
        session.SendPacket(packet);
    }

    return true;
}

IMPLEMENT_HANDLER(PrototypeServerSession, PS2C_Auth)
{
    LOG_INFO(LOG_FILTER_CLIENT, "FromServer(Auth): {}", packet.auth_result());

    return true;
}

} // namespace XP