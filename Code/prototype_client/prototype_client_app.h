#pragma once
#include "client_app.h"
#include "prototype_server_session.h"

namespace XP
{

class PrototypeClientApp : public ClientApp<PrototypeServerSession>
{
public:
    explicit PrototypeClientApp();
    virtual ~PrototypeClientApp();

public:
    virtual bool Initialize(AppConfig&& appConfig) override;
    virtual bool Run() override;

    void SendAuth(const std::wstring& id, const std::wstring& password);
};

} // namespace XP

#define g_PrototypeClientApp SINGLETON_STATIC(XP::PrototypeClientApp)