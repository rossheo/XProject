#pragma once
#include "app_config.h"

namespace XP
{

template <typename TSession>
class ClientApp
{
public:
    explicit ClientApp();
    virtual ~ClientApp();

protected:
    virtual bool Initialize(AppConfig&& appConfig);
    virtual bool Run();
    virtual void Clear() noexcept;

public:
    virtual void AsyncRun();
    virtual void SendMessage(const std::wstring& message);

private:
    virtual void PostReceive();

protected:
    std::shared_ptr<TSession> _spServerSession;

private:
    AppConfig _appConfig;
    bool _isInitialized;

    boost::asio::io_service _ioservice;
};

template <typename TSession>
ClientApp<TSession>::ClientApp()
    : _isInitialized(false)
{
}

template <typename TSession>
ClientApp<TSession>::~ClientApp()
{
    Clear();
}

template <typename TSession>
bool ClientApp<TSession>::Initialize(AppConfig&& appConfig)
{
    _appConfig = std::move(appConfig);
    _appConfig.Initialize();

    try
    {
        boost::asio::ip::tcp::endpoint endPoint(
            boost::asio::ip::address::from_string(ToUTF8(_appConfig.GetAddress())),
            _appConfig.GetPort());

        _spServerSession = std::make_shared<TSession>(_ioservice);
        ASSERT(_spServerSession);
        _spServerSession->Connect(endPoint);

        PostReceive();
    }
    catch (const boost::system::error_code& errorCode)
    {
        LOG_ERROR(LOG_FILTER_CLIENT, "Fail to initialized. {}", errorCode);
        return false;
    }
    catch (const std::exception& ex)
    {
        LOG_ERROR(LOG_FILTER_CLIENT, "Fail to initialized. {}", ex);
        return false;
    }

    _isInitialized = true;
    return true;
}

template <typename TSession>
bool ClientApp<TSession>::Run()
{
    if (!_isInitialized)
    {
        LOG_INFO(LOG_FILTER_CLIENT, "{} is not initialized.", _appConfig.GetAppName());
        return false;
    }

    LOG_INFO(LOG_FILTER_CLIENT, "{} is running.", _appConfig.GetAppName());

    _ioservice.run();
    return true;
}

template <typename TSession>
void ClientApp<TSession>::AsyncRun()
{
    if (!_isInitialized)
    {
        LOG_INFO(LOG_FILTER_CLIENT, "{} is not initialized.", _appConfig.GetAppName());
        return;
    }

    LOG_INFO(LOG_FILTER_CLIENT, "{} is running.", _appConfig.GetAppName());

    boost::thread thread(boost::bind(&boost::asio::io_service::run, &_ioservice));
    thread.detach();
}

template <typename TSession>
void ClientApp<TSession>::Clear() noexcept
{
    _isInitialized = false;

    if (_spServerSession)
        _spServerSession.reset();

    if (!_ioservice.stopped())
        _ioservice.stop();

    LOG_INFO(LOG_FILTER_CLIENT, "{} is stopped.", _appConfig.GetAppName());
}

template <typename TSession>
void ClientApp<TSession>::PostReceive()
{
    if (!_spServerSession)
    {
        LOG_ERROR(LOG_FILTER_CLIENT, "_spServerSession is nullptr.");
        return;
    }

    _spServerSession->PostReceive();
}

template <typename TSession>
void ClientApp<TSession>::SendMessage(const std::wstring& message)
{
    if (!_spServerSession)
    {
        LOG_ERROR(LOG_FILTER_CLIENT, "_spServerSession is nullptr.");
        return;
    }

    _spServerSession->SendMessage(message);
}

} // namespace XP
