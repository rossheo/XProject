#pragma once

#include "packet_define.h"
#include "server_client.pb.h"

namespace PS2C
{
    enum ProtocolNumber : uint16
    {
        Chat,
        Auth,
    };
}

DECLARE_PACKET_TYPE(PS2C, Chat);
DECLARE_PACKET_TYPE(PS2C, Auth);
