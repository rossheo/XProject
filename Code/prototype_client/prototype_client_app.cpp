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

void PrototypeClientApp::SendAuth(const std::wstring& id, const std::wstring& password)
{
    if (!_spServerSession)
    {
        LOG_ERROR(LOG_FILTER_CLIENT, "_spServerSession is nullptr.");
        return;
    }

    _spServerSession->SendAuth(id, password);
}

} // namespace XP
