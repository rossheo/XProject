#include "stdafx.h"
#include "prototype_client_app.h"

namespace XP
{

PrototypeClientApp::PrototypeClientApp()
{
}


PrototypeClientApp::~PrototypeClientApp()
{
}

bool PrototypeClientApp::Initialize(AppConfig&& appConfig)
{
    if (!ClientApp::Initialize(std::move(appConfig)))
        return false;

    return true;
}

bool PrototypeClientApp::Run()
{
    if (!ClientApp::Run())
        return false;

    return true;
}

} // namespace XP
