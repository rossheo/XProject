#pragma once

#include "app_config.h"
#include "session_manager.h"

namespace XP
{

template <typename TSession>
class ServerApp
{
public:
    explicit ServerApp();
    virtual ~ServerApp();

protected:
    virtual bool Initialize(AppConfig&& appConfig);
    virtual bool Run();
    virtual void Clear() noexcept;

private:
    virtual void PostAccept();

protected:
    SessionManager<TSession> _sessionManager;

private:
    AppConfig _appConfig;
    bool _isInitialized;

    boost::asio::io_service _ioservice;
    boost::asio::ip::tcp::acceptor _acceptor;
};

template <typename TSession>
ServerApp<TSession>::ServerApp()
    : _isInitialized(false)
    , _acceptor(_ioservice)
{
}

template <typename TSession>
ServerApp<TSession>::~ServerApp()
{
    Clear();
}

template <typename TSession>
bool ServerApp<TSession>::Initialize(AppConfig&& appConfig)
{
    _appConfig = std::move(appConfig);
    _appConfig.Initialize();

    try
    {
        boost::asio::ip::tcp::endpoint endPoint(
            boost::asio::ip::tcp::v4(), _appConfig.GetPort());

        _acceptor.open(endPoint.protocol());
        _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor.bind(endPoint);
        _acceptor.listen();

        PostAccept();
    }
    catch (const boost::system::error_code& errorCode)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "Fail to initialized. {}", errorCode);
        return false;
    }
    catch (const std::exception& ex)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "Fail to initialized. {}", ex);
        return false;
    }

    const auto& local_endpoint = _acceptor.local_endpoint();
    LOG_INFO(LOG_FILTER_SERVER, "{} is initialized. ip: {}, port: {}",
        _appConfig.GetAppName(),
        local_endpoint.address().to_string(),
        local_endpoint.port());

    _isInitialized = true;
    return true;
}

template <typename TSession>
bool ServerApp<TSession>::Run()
{
    if (!_isInitialized)
    {
        LOG_INFO(LOG_FILTER_SERVER, "{} is not initialized.", _appConfig.GetAppName());
        return false;
    }

    LOG_INFO(LOG_FILTER_SERVER, "{} is running.", _appConfig.GetAppName());
    _ioservice.run();
    return true;
}

template <typename TSession>
void ServerApp<TSession>::Clear() noexcept
{
    _isInitialized = false;

    boost::system::error_code errorCode;
    _acceptor.close(errorCode);
    if (errorCode)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "Acceptor close exception. {}", errorCode);
    }

    if (!_ioservice.stopped())
        _ioservice.stop();

    LOG_INFO(LOG_FILTER_SERVER, "{} is stopped.", _appConfig.GetAppName());
}

template <typename TSession>
void ServerApp<TSession>::PostAccept()
{
    std::shared_ptr<TSession> spServerSession = _sessionManager.CreateSession(_ioservice);
    if (!spServerSession)
    {
        LOG_ERROR(LOG_FILTER_SERVER, "PostAccept fail to create session.");
        return;
    }

    auto& serverSocket = spServerSession->GetSocket();
    _acceptor.async_accept(serverSocket,
        [this, spServerSessionMoved = std::move(spServerSession)]
    (const boost::system::error_code& errorCode)
    {
        if (errorCode)
        {
            LOG_ERROR(LOG_FILTER_SERVER, "Fail to PostAccept. {}", errorCode);

            _sessionManager.RemoveSession(spServerSessionMoved.get());
            return;
        }

        if (!spServerSessionMoved->PostReceive())
        {
            _sessionManager.RemoveSession(spServerSessionMoved.get());
        }

        spServerSessionMoved->OnConnect();

        PostAccept();
    });
}

} // namespace XP
