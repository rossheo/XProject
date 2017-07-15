#include "stdafx.h"
#include "echo_server_app.h"

namespace XP
{

EchoServerApp::EchoServerApp()
    : ServerApp()
{
}

EchoServerApp::~EchoServerApp()
{
}

bool EchoServerApp::Initialize(AppConfig&& appConfig)
{
    if (!ServerApp::Initialize(std::move(appConfig)))
        return false;

    return true;
}

bool EchoServerApp::Run()
{
    if (!ServerApp::Run())
        return false;

    return true;
}

SessionManager<EchoClientSession>& EchoServerApp::GetSessionManager()
{
    return _sessionManager;
}

} // namespace XP
