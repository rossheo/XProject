// echo_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "echo_server_app.h"

int main()
{
    using namespace XP;

    std::locale::global(std::locale("korean"));
    std::wcout.imbue(std::locale("korean"));

    AppConfig appConfig(TEXT("EchoServerApp"), TEXT("echo_server_log4cplus.property"));
    appConfig.SetPort(1280);

    if (g_EchoServerApp.Initialize(std::move(appConfig)))
    {
        g_EchoServerApp.Run();
    }

    return 0;
}
