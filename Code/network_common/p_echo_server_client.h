#pragma once

#include "packet_define.h"
#include "echo_server_client.pb.h"

namespace pb_echo
{

DECLARE_PACKET_TYPE(PS2C, Chat);

} // namespace pb_echo

using namespace pb_echo;