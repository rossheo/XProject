#pragma once

namespace pb_prototype
{
class UnitId;
}

namespace XP
{

BETTER_ENUM(eUnitType, int,\
    INVALID = 0,\
    PLAYER_UNIT,\
    NPC_UNIT);

class UnitId
{
public:
    static const UnitId INVALID;
    static const uint32 MIN_ID_VALUE = 1;
    static const uint32 MAX_ID_VALUE = 0x00FFFFFF;

public:
    explicit UnitId();
    explicit UnitId(eUnitType unitType, uint32 id);
    UnitId(const UnitId& rhs);
    ~UnitId();

    UnitId& operator= (const UnitId& rhs);

    UnitId& operator= (const int8& rhs) = delete;
    UnitId& operator= (const uint8& rhs) = delete;
    UnitId& operator= (const int16& rhs) = delete;
    UnitId& operator= (const uint16& rhs) = delete;
    UnitId& operator= (const int32& rhs) = delete;
    UnitId& operator= (const uint32& rhs) = delete;
    UnitId& operator= (const int64& rhs) = delete;
    UnitId& operator= (const uint64& rhs) = delete;

    void To(pb_prototype::UnitId& pbUnitId) const;
    void From(const pb_prototype::UnitId& pbUnitId);

    explicit operator uint32() const { return *reinterpret_cast<const uint32*>(this); }
    bool IsInvalid() const
    {
        return static_cast<uint32>(*this) == static_cast<uint32>(INVALID); 
    }

public:
    uint32 GetId() const { return _id; }
    eUnitType GetType() const { return eUnitType::_from_integral(_type); }
    std::string GetString() const;
    std::wstring GetWString() const;

private:
    uint32 _type : 8;
    uint32 _id : 24;
};

inline bool operator< (const UnitId& lhs, const UnitId& rhs)
{
    return static_cast<uint32>(lhs) < static_cast<uint32>(rhs);
}
inline bool operator>  (const UnitId& lhs, const UnitId& rhs) { return rhs < lhs; }
inline bool operator<= (const UnitId& lhs, const UnitId& rhs) { return !(lhs > rhs); }
inline bool operator>= (const UnitId& lhs, const UnitId& rhs) { return !(lhs < rhs); }

inline bool operator== (const UnitId& lhs, const UnitId& rhs)
{
    return static_cast<uint32>(lhs) == static_cast<uint32>(rhs);
}
inline bool operator!= (const UnitId& lhs, const UnitId& rhs) { return !(lhs == rhs); }

} // namespace XP

template <>
struct std::hash<XP::UnitId>
    : public std::unary_function<XP::UnitId, std::size_t>
{
public:
    typedef XP::UnitId _Kty;

    std::size_t operator()(const _Kty& _Keyval) const
    {
        return (std::hash<uint32>()(static_cast<uint32>(_Keyval)));
    }
};

template <>
struct boost::hash<XP::UnitId>
    : public std::unary_function<XP::UnitId, std::size_t>
{
public:
    typedef XP::UnitId _Kty;

    std::size_t operator()(const _Kty& _Keyval) const
    {
        return (boost::hash<uint32>()(static_cast<uint32>(_Keyval)));
    }
};
