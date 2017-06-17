// prototype_server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "prototype_server_app.h"

int main()
{
    using namespace XP;

    std::locale::global(std::locale("korean"));
    std::wcout.imbue(std::locale("korean"));

    AppConfig appConfig(TEXT("PrototypeServerApp"), TEXT("prototype_server_log4cplus.property"));
    appConfig.SetPort(1280);

    if (g_PrototypeServerApp.Initialize(std::move(appConfig)))
    {
        g_PrototypeServerApp.Run();
    }

    return 0;
}

