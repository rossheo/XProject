#pragma once

#include "packet_define.h"
#include "echo_client_server.pb.h"

namespace pb_echo
{

DECLARE_PACKET_TYPE(PC2S, Chat);

} // namespace pb_echo

using namespace pb_echo;