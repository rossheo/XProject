#pragma once
#include "client_app.h"
#include "server_session.h"

namespace XP
{

class PrototypeClientApp : public ClientApp<ServerSession>
{
public:
    explicit PrototypeClientApp();
    virtual ~PrototypeClientApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;
};

} // namespace XP

#define g_PrototypeClientApp SINGLETON_STATIC(XP::PrototypeClientApp)