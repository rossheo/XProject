#pragma once

#define DECLARE_PACKET_NAME(direction, enumValue) direction##_##enumValue
#define DECLARE_PROTOBUF_NAME(direction, enumValue) direction##::##enumValue
#define DECLARE_PROTOCOL_NUMBER(direction, enumValue) direction##::ProtocolNumber::##enumValue

#define DECLARE_PACKET_TYPE(direction, enumValue)\
class DECLARE_PACKET_NAME(direction, enumValue) : public DECLARE_PROTOBUF_NAME(direction, enumValue)\
{\
public:\
    DECLARE_PACKET_NAME(direction, enumValue)() {}\
    virtual ~ DECLARE_PACKET_NAME(direction, enumValue)() {}\
    static const uint16 PROTOCOL_NUMBER = DECLARE_PROTOCOL_NUMBER(direction, enumValue);\
};
