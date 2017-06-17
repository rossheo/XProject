// echo_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "echo_client_app.h"

int main()
{
    using namespace XP;

    std::locale::global(std::locale("korean"));
    std::wcout.imbue(std::locale("korean"));

    AppConfig appConfig(L"EchoClientApp", L"echo_client_log4cplus.property");
    appConfig.SetAddress("127.0.0.1");
    appConfig.SetPort(1280);

    if (g_EchoClientApp.Initialize(std::move(appConfig)))
    {
        g_EchoClientApp.AsyncRun();

        std::array<wchar_t, 512> inputMessage = {0};
        while (std::wcin.getline(inputMessage.data(), inputMessage.size()))
        {
            std::wstring message(inputMessage.data());
            if (message == TEXT("quit"))
            {
                LOG_INFO(LOG_FILTER_CLIENT, "quit client.");
                break;
            }

            g_EchoClientApp.SendMessage(message);
            inputMessage.fill('\0');
        }
    }

    return 0;
}
