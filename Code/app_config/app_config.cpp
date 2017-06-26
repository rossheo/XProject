#include "stdafx.h"
#include "app_config.h"

namespace XP
{

AppConfig::AppConfig()
    : _port(0)
{
}

AppConfig::AppConfig(const std::wstring& appName,
    const std::wstring& logfilePropertyName)
    : _appName(appName)
    , _logFilePropertyName(logfilePropertyName)
    , _port(0)
{
}

AppConfig::AppConfig(AppConfig&& appConfig)
    : _port(0)
{
    *this = std::move(appConfig);
}

AppConfig::~AppConfig()
{
    Cleanup();
}

AppConfig& AppConfig::operator=(AppConfig&& appConfig)
{
    if (this != &appConfig)
    {
        _appName = std::move(appConfig._appName);
        _logFilePropertyName = std::move(appConfig._logFilePropertyName);
        _ipAddress = std::move(appConfig._ipAddress);
        _port = appConfig._port;
    }

    return *this;
}

void AppConfig::Initialize()
{
    InitWorkingDirectory();
    CreateLogDirectory();
    InitLog4cplus();
}

std::wstring AppConfig::GetWorkingDirectory() const
{
    std::array<wchar_t, MAX_PATH> pathBuffer = {0};
    GetModuleFileNameW(NULL, pathBuffer.data(), static_cast<DWORD>(pathBuffer.max_size()));

    boost::filesystem::path path(pathBuffer.data());
    path = path.parent_path();
    path = path.parent_path();

    return path.generic_wstring();
}

std::wstring AppConfig::GetAppName() const
{
    return _appName;
}

void AppConfig::InitLog4cplus() noexcept
{
    if (_logFilePropertyName.empty())
    {
        LOG_ERROR(LOG_FILTER_SYSTEM, "logfile property name is empty.");
    }

    log4cplus::initialize();
    log4cplus::PropertyConfigurator::doConfigure(_logFilePropertyName.c_str());
}

void AppConfig::InitWorkingDirectory() noexcept
{
    const std::wstring& workingDirectory = GetWorkingDirectory();
    SetCurrentDirectoryW(workingDirectory.c_str());
}

void AppConfig::CreateLogDirectory() noexcept
{
    boost::filesystem::path logPath(GetWorkingDirectory());
    logPath /= TEXT("logs");
    boost::filesystem::create_directories(logPath);
}

void AppConfig::Cleanup() noexcept
{
    log4cplus::Logger::shutdown();
}

void AppConfig::SetAddress(const std::wstring& ipAddress)
{
    _ipAddress = ipAddress;
}

std::wstring AppConfig::GetAddress() const
{
    return _ipAddress;
}

void AppConfig::SetPort(uint16 port)
{
    _port = port;
}

uint16 AppConfig::GetPort() const
{
    return _port;
}

} // namespace XP
