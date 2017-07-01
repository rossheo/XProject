#include "stdafx.h"
#include "prototype_client_session.h"

#include "prototype_server_app.h"
#include "player_unitdata.h"
#include "unit_lock.h"
#include "unit_id.h"
#include "prototype_unitlock.h"

#include "p_prototype_client_server.h"
#include "p_prototype_server_client.h"

namespace XP
{

DECLARE_HANDLER(PrototypeClientSession, PC2S_Chat);
DECLARE_HANDLER(PrototypeClientSession, PC2S_Auth);
DECLARE_HANDLER(PrototypeClientSession, PC2S_Rename);

IMPLEMENT_INITIALIZE(PrototypeClientSession)
{
    REGISTER_HANDLER(PC2S_Chat);
    REGISTER_HANDLER(PC2S_Auth);
    REGISTER_HANDLER(PC2S_Rename);
}

IMPLEMENT_HANDLER(PrototypeClientSession, PC2S_Chat)
{
    const auto& remoteEndpoint = session.GetSocket().remote_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "IP:{}, PORT:{}, Message:{}",
        remoteEndpoint.address().to_string(),
        remoteEndpoint.port(),
        FromUTF8(packet.message()));

    PS2C_Chat out;
    out.set_message(packet.message());
    session.SendPacket(out);
}

IMPLEMENT_HANDLER(PrototypeClientSession, PC2S_Auth)
{
    const auto& remoteEndpoint = session.GetSocket().remote_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "IP:{}, PORT:{}, ID:{}, PW:{}",
        remoteEndpoint.address().to_string(),
        remoteEndpoint.port(),
        FromUTF8(packet.id()),
        FromUTF8(packet.password()));

    bool login_result = false;
    if (packet.id() == "proto_id" && packet.password() == "proto_pw")
        login_result = true;

    PlayerUnitData playerUnitData;
    playerUnitData.SetName(TEXT("proto_player"));

    PlayerUnit* pPlayerUnit =
        g_PrototypeServerApp.CreatePlayer(session, std::move(playerUnitData));
    if (!pPlayerUnit)
    {
        login_result = false;
    }

    PS2C_Auth out;
    out.set_auth_result(login_result);
    if (auto pPlayerUnitData = out.mutable_player_unit_data())
        pPlayerUnitData->set_name(ToUTF8(playerUnitData.GetName()));
    session.SendPacket(out);
}

IMPLEMENT_HANDLER(PrototypeClientSession, PC2S_Rename)
{
    using namespace XP;
    const UnitId unitId = session.GetUnitId();

    UnitScopeLock<PrototypeUnitLock> unitScopeLock({ unitId });
    PlayerUnit* pPlayer = UnitLock::GetPlayerUnit(unitId);
    if (!pPlayer)
        return;

    std::wstring name = pPlayer->GetName();

    pPlayer->SetName(FromUTF8(packet.name()));

    LOG_INFO(LOG_FILTER_SERVER, "Player Rename. {} -> {}", name, pPlayer->GetName());
}

} // namespace XP
