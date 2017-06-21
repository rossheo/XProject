#include "stdafx.h"
#include "packet_buffer.h"

PacketBuffer::PacketBuffer()
    : _readPos(0)
    , _writePos(0)
{
    _buffer.resize(MAX_BUF_SIZE);
}

PacketBuffer::PacketBuffer(const char* pBuffer, uint16 size)
    : _readPos(0)
    , _writePos(0)
{
    ASSERT(size <= MAX_BUF_SIZE);

    _buffer.resize(size);
    AppendBuffer(pBuffer, size);
}

PacketBuffer::PacketBuffer(const PacketBuffer& rhs)
    : _readPos(0)
    , _writePos(0)
{
    _buffer.resize(rhs.GetBufferSize());
    AppendBuffer(rhs);
}

PacketBuffer::~PacketBuffer()
{
    Clear();
};

uint16 PacketBuffer::GetPacketNo() const
{
    if (_writePos < GetHeaderSize())
    {
        LOG_ERROR(LOG_FILTER_PACKET_BUFFER, "Not enough data.");
        return 0;
    }

    uint16 packetNo = 0;
    CopyMemory(&packetNo, _buffer.data() + _readPos + sizeof(uint16), sizeof(uint16));
    return packetNo;
}

bool PacketBuffer::IsEmptyData() const
{
    return (_readPos == _writePos);
}

bool PacketBuffer::IsNotEnoughBuffer() const
{
    return (GetRemainSize() < MIN_BUF_SIZE);
}

bool PacketBuffer::IsAbleToGetPacket() const
{
    const uint16 packetSize = GetPacketSize();
    if (packetSize == 0)
        return false;

    const uint16 packetBufferSize = GetBufferSize();
    if (packetBufferSize == 0)
        return false;

    return (packetSize <= packetBufferSize);
}

void PacketBuffer::ConsumePacket()
{
    const uint16 packetSize = GetPacketSize();
    TruncateBuffer(packetSize);
}

void PacketBuffer::TruncateBuffer(uint16 size)
{
    if (size > GetBufferSize())
    {
        LOG_ERROR(LOG_FILTER_PACKET_BUFFER,
            "Fail to truncate buffer. remain size: {}, truncate size: {}",
            (_writePos - _readPos), size);
        return;
    }

    _readPos += size;
}

bool PacketBuffer::AppendWriteSize(uint16 size)
{
    if (size > GetRemainSize())
    {
        LOG_ERROR(LOG_FILTER_PACKET_BUFFER, "Not enough remain buffer.");
        return false;
    }

    _writePos += size;
    return true;
}

void PacketBuffer::ReArrange()
{
    const uint16 bufferSize = GetBufferSize();
    MoveMemory(_buffer.data(), GetBuffer(), bufferSize);
    _readPos = 0;
    _writePos = bufferSize;
}

char* PacketBuffer::GetMutableBuffer()
{
    return reinterpret_cast<char*>(_buffer.data() + _readPos);
}

const char* PacketBuffer::GetBuffer() const
{
    return _buffer.data() + _readPos;
}

uint16 PacketBuffer::GetBufferSize() const
{
    if (_readPos > _writePos)
    {
        LOG_ERROR(LOG_FILTER_PACKET_BUFFER, "Not enough buffer size.");
        return 0;
    }

    return _writePos - _readPos;
}

const char* PacketBuffer::GetPacketBuffer() const
{
    return GetBuffer();
}

uint16 PacketBuffer::GetPacketSize() const
{
    const uint16 bufferSize = GetBufferSize();
    if (bufferSize < sizeof(uint16))
        return 0;

    uint16 packetSize = 0;
    CopyMemory(&packetSize, _buffer.data() + _readPos, sizeof(packetSize));
    return packetSize;
}

const char* PacketBuffer::GetPayloadBuffer() const
{
    return GetBuffer() + GetHeaderSize();
}

uint16 PacketBuffer::GetPayloadBufferSize() const
{
    return GetPacketSize() - GetHeaderSize();
}

bool PacketBuffer::AppendBuffer(const PacketBuffer& packetBuffer) noexcept
{
    return AppendBuffer(packetBuffer.GetBuffer(), packetBuffer.GetBufferSize());
}

void PacketBuffer::Clear() noexcept
{
    _readPos = 0;
    _writePos = 0;
}

bool PacketBuffer::AppendBuffer(const char* pBuffer, uint16 size) noexcept
{
    if (!pBuffer)
        return false;

    if (size == 0)
        return false;

    if (size > GetRemainSize())
    {
        ReArrange();
    }

    if (size > GetRemainSize())
    {
        LOG_ERROR(LOG_FILTER_PACKET_BUFFER, "Not enough remain buffer.");
        return false;
    }

    CopyMemory(_buffer.data() + _writePos, pBuffer, size);
    _writePos += size;
    return true;
}

bool PacketBuffer::SetPacketSize(uint16 packetSize)
{
    if (packetSize > MAX_BUF_SIZE)
    {
        LOG_ERROR(LOG_FILTER_PACKET_BUFFER, 
            "packet size is bigger than MAX_BUF_SIZE. packetSize: {}",
            packetSize);
        return false;
    }

    CopyMemory(_buffer.data() + _writePos, &packetSize, sizeof(packetSize));
    _writePos += sizeof(packetSize);
    return true;
}

bool PacketBuffer::SetPacketNo(uint16 packetNo)
{
    CopyMemory(_buffer.data() + _writePos, &packetNo, sizeof(packetNo));
    _writePos += sizeof(packetNo);
    return true;
}
