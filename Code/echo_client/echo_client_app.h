#pragma once
#include "client_app.h"
#include "server_session.h"

namespace XP
{

class EchoClientApp : public ClientApp<ServerSession>
{
public:
    explicit EchoClientApp();
    virtual ~EchoClientApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;
};

} // namespace XP

#define g_EchoClientApp SINGLETON_STATIC(XP::EchoClientApp)