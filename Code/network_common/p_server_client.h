#pragma once

#include "packet_define.h"
#include "server_client.pb.h"

namespace PS2C
{
    enum ProtocolNumber : uint16
    {
        Chat,
    };
}

DECLARE_PACKET_TYPE(PS2C, Chat);
