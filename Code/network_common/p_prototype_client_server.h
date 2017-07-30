#pragma once

#include "packet_define.h"
#include "prototype_client_server.pb.h"

namespace pb_prototype
{

DECLARE_PACKET_TYPE(PC2S, Chat);
DECLARE_PACKET_TYPE(PC2S, Auth);
DECLARE_PACKET_TYPE(PC2S, Rename);

} // namespace pb_prototype

using namespace pb_prototype;