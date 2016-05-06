#pragma once

namespace XP
{

class AppConfig
{
public:
    explicit AppConfig();
    explicit AppConfig(const std::wstring& appName,
        const std::wstring& logfilePropertyName);
    explicit AppConfig(AppConfig&& appConfig);
    ~AppConfig();

    AppConfig& operator=(AppConfig&& appConfig);
    AppConfig& operator=(const AppConfig&) = delete;

public:
    void Initialize();
    std::wstring GetWorkingDirectory() const;

    std::wstring GetAppName() const;
    void SetAddress(const std::string& ipAddress);
    std::string GetAddress() const;
    void SetPort(uint16 port);
    uint16 GetPort() const;

private:
    void InitLog4cplus() noexcept;
    void InitWorkingDirectory() noexcept;
    void Cleanup() noexcept;

private:
    std::wstring _appName;
    std::wstring _logFilePropertyName;
    std::string _ipAddress;
    uint16 _port;
};

} // namespace XP
