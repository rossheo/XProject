#pragma once

#include "packet_define.h"
#include "echo_server_client.pb.h"

namespace echo
{
namespace PS2C
{
enum ProtocolNumber : uint16
{
    Chat,
};

} // namespace PS2C

DECLARE_PACKET_TYPE(PS2C, Chat);

} // namespace echo

using namespace echo;