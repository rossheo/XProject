#pragma once

#include "packet_define.h"
#include "client_server.pb.h"

namespace PC2S
{
    enum ProtocolNumber : uint16
    {
        Chat,
        Auth,
        Rename
    };
}

DECLARE_PACKET_TYPE(PC2S, Chat);
DECLARE_PACKET_TYPE(PC2S, Auth);
DECLARE_PACKET_TYPE(PC2S, Rename);
