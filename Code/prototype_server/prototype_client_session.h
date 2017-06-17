#pragma once
#include "session.h"

namespace XP
{

class PrototypeClientSession : public Session<PrototypeClientSession>
{
public:
    explicit PrototypeClientSession(boost::asio::io_service& ioservice);
    virtual ~PrototypeClientSession();
};

} // namespace XP

