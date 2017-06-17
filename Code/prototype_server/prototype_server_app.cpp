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

} // namespace XP
