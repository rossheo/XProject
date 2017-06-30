#include "stdafx.h"
#include "prototype_server_session.h"

#include "p_client_server.h"
#include "p_server_client.h"

namespace XP
{

DECLARE_HANDLER(PrototypeServerSession, PS2C_Who);
DECLARE_HANDLER(PrototypeServerSession, PS2C_Chat);
DECLARE_HANDLER(PrototypeServerSession, PS2C_Auth);

IMPLEMENT_INITIALIZE(PrototypeServerSession)
{
    REGISTER_HANDLER(PS2C_Who);
    REGISTER_HANDLER(PS2C_Chat);
    REGISTER_HANDLER(PS2C_Auth);
}

IMPLEMENT_HANDLER(PrototypeServerSession, PS2C_Who)
{
    PC2S_Auth out;
    out.set_id("proto_id");
    out.set_password("proto_pw");
    session.SendPacket(out);
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
}

IMPLEMENT_HANDLER(PrototypeServerSession, PS2C_Auth)
{
    LOG_INFO(LOG_FILTER_CLIENT, "FromServer(Auth): {}", packet.auth_result());
    LOG_INFO(LOG_FILTER_CLIENT, "PlayerUnitData: {}", packet.player_unit_data().name());

    PC2S_Rename out;
    out.set_name(ToUTF8(TEXT("player_rename")));
    session.SendPacket(out);
}

} // namespace XP