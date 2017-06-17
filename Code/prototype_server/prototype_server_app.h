#pragma once

#include "server_app.h"
#include "client_session.h"

namespace XP
{
class PrototypeServerApp : public ServerApp<ClientSession>
{
public:
    explicit PrototypeServerApp();
    virtual ~PrototypeServerApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;
};

} // namespace XP

#define g_PrototypeServerApp SINGLETON_STATIC(XP::PrototypeServerApp)

