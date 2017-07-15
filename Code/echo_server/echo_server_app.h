#pragma once

#include "server_app.h"
#include "echo_client_session.h"

namespace XP
{

class EchoServerApp : public ServerApp<EchoClientSession>
{
public:
    explicit EchoServerApp();
    virtual ~EchoServerApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;

    SessionManager<EchoClientSession>& GetSessionManager();
};

} // namespace XP

#define g_EchoServerApp SINGLETON_STATIC(XP::EchoServerApp)
#define g_SessionManager g_EchoServerApp.GetSessionManager()
