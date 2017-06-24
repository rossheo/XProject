#pragma once
#include "session.h"

namespace XP
{

class ClientSession : public Session<ClientSession>
{
public:
    explicit ClientSession(boost::asio::io_service& ioservice,
        SessionManager<ClientSession>* pSessionManager);
    virtual ~ClientSession();
};

} // namespace XP
