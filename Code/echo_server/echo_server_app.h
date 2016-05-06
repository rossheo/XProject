#pragma once

#include "server_app.h"
#include "client_session.h"

namespace XP
{

class EchoServerApp : public ServerApp<ClientSession>
{
public:
    explicit EchoServerApp();
    virtual ~EchoServerApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;
};

} // namespace XP

#define g_EchoServerApp SINGLETON_STATIC(XP::EchoServerApp)
