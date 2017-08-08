#include "stdafx.h"
#include "prototype_client_session.h"
#include "prototype_server_app.h"

#include "p_prototype_server_client.h"

namespace XP
{

PrototypeClientSession::PrototypeClientSession(boost::asio::io_service& ioservice,
    SessionManager<PrototypeClientSession>* pSessionManager)
    : Session(ioservice, pSessionManager)
{
}

PrototypeClientSession::~PrototypeClientSession()
{
    if (_pSessionManager)
        _pSessionManager->RemoveSession(this);
}

void PrototypeClientSession::OnConnect()
{
    __super::OnConnect();

    PS2C_Who out;
    out.set_message("ProtoTypeServer");
    SendPacket(out);
}

void PrototypeClientSession::OnDisconnect(
    boost::asio::socket_base::shutdown_type shutdownType)
{
    __super::OnDisconnect(shutdownType);
}

UnitId PrototypeClientSession::GetUnitId() const
{
    UnitId unitId;
    _pSessionManager->Get(this, unitId);
    return unitId;
}

} // namespace XP
