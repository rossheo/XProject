#include "stdafx.h"
#include "prototype_server_app.h"

namespace XP
{

PrototypeServerApp::PrototypeServerApp()
    : ServerApp()
{
}

PrototypeServerApp::~PrototypeServerApp()
{
}

bool PrototypeServerApp::Initialize(AppConfig&& appConfig)
{
    if (!ServerApp::Initialize(std::move(appConfig)))
        return false;

    return true;
}

bool PrototypeServerApp::Run()
{
    if (ServerApp::Run())
        return false;

    return true;
}

void PrototypeServerApp::RemoveSession(const PrototypeClientSession* pSession)
{
    ASSERT(pSession);
    RemovePlayer(pSession);
    __super::RemoveSession(pSession);
}

bool PrototypeServerApp::CreatePlayer(const PrototypeClientSession& session,
    PlayerUnitData&& playerUnitData)
{
    PlayerUnit* pPlayerUnit = _unitManager.CreatePlayerUnit(std::move(playerUnitData));
    if (!pPlayerUnit)
        return false;

    _sessionManager.AssociateUnitWithSession(session, *pPlayerUnit);
    return true;
}

void PrototypeServerApp::RemovePlayer(const PrototypeClientSession* pSession)
{
    ASSERT(pSession);

    PlayerUnit* pPlayerUnit = nullptr;
    if (!_sessionManager.Get(pSession, pPlayerUnit))
        return;

    _unitManager.ReleaseUnit(pPlayerUnit);
}

} // namespace XP