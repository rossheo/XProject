#pragma once

#include "packet_define.h"
#include "prototype_server_client.pb.h"

namespace pb_prototype
{
namespace PS2C
{
enum ProtocolNumber : uint16
{
    Who,
    Chat,
    Auth,
};

} // namespace PS2C

DECLARE_PACKET_TYPE(PS2C, Who);
DECLARE_PACKET_TYPE(PS2C, Chat);
DECLARE_PACKET_TYPE(PS2C, Auth);

} // namespace pb_prototype

using namespace pb_prototype;