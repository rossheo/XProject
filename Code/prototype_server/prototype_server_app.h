#pragma once

#include "server_app.h"
#include "prototype_client_session.h"
#include "prototype_unit_manager.h"

namespace XP
{

class PlayerUnitData;

class PrototypeServerApp : public ServerApp<PrototypeClientSession>
{
public:
    explicit PrototypeServerApp();
    virtual ~PrototypeServerApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;

    PrototypeUnitManager& GetUnitManager();
    SessionManager<PrototypeClientSession>& GetSessionManager();

    PlayerUnit* CreatePlayer(const PrototypeClientSession& session,
        PlayerUnitData&& playerUnitData);

private:
    void RemovePlayer(const PrototypeClientSession* pSession);

private:
    PrototypeUnitManager _unitManager;
};

} // namespace XP

#define g_PrototypeServerApp SINGLETON_STATIC(XP::PrototypeServerApp)
#define g_UnitManager g_PrototypeServerApp.GetUnitManager()
#define g_SessionManager g_PrototypeServerApp.GetSessionManager()

