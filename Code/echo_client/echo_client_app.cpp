#include "stdafx.h"
#include "echo_client_app.h"

namespace XP
{
EchoClientApp::EchoClientApp()
    : ClientApp()
{
}

EchoClientApp::~EchoClientApp()
{
}

bool EchoClientApp::Initialize(AppConfig&& appConfig)
{
    if (!ClientApp::Initialize(std::move(appConfig)))
        return false;

    return true;
}

bool EchoClientApp::Run()
{
    if (!ClientApp::Run())
        return false;

    return true;
}

} // namespace XP