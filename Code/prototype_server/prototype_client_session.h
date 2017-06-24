#pragma once
#include "session.h"

namespace XP
{

class PrototypeClientSession : public Session<PrototypeClientSession>
{
public:
    explicit PrototypeClientSession(boost::asio::io_service& ioservice,
        SessionManager<PrototypeClientSession>* pSessionManager);
    virtual ~PrototypeClientSession();

    void OnConnect();
    void OnDisconnect(boost::asio::socket_base::shutdown_type shutdownType);

    UnitId GetUnitId() const;
};

} // namespace XP

