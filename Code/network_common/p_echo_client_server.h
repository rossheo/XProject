#pragma once

#include "packet_define.h"
#include "echo_client_server.pb.h"

namespace echo
{
namespace PC2S
{
enum ProtocolNumber : uint16
{
    Chat,
};

} // namespace PC2S

DECLARE_PACKET_TYPE(PC2S, Chat);

} // namespace echo

using namespace echo;