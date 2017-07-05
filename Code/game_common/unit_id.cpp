#include "stdafx.h"
#include "unit_id.h"
#include "prototype_common.pb.h"

namespace XP
{

const UnitId UnitId::INVALID;

UnitId::UnitId()
    : _type(0)
    , _id(0)
{
}

UnitId::UnitId(eUnitType unitType, uint32 id)
    : _type(unitType._to_integral())
    , _id(id)
{
    ASSERT(_id <= MAX_ID_VALUE);
}

UnitId::UnitId(const UnitId& rhs)
    : _type(rhs._type)
    , _id(rhs._id)
{
    ASSERT(_id <= MAX_ID_VALUE);
}

UnitId::~UnitId()
{
    _type = 0;
    _id = 0;
}

void UnitId::To(pb_prototype::UnitId& pbUnitId) const
{
    pbUnitId.set_unit_type(GetType());
    pbUnitId.set_unit_id(GetId());
}

void UnitId::From(const pb_prototype::UnitId& pbUnitId)
{
    _type = pbUnitId.unit_type();
    _id = pbUnitId.unit_id();
}

std::wstring UnitId::GetString() const
{
    return fmt::format(TEXT("UnitId(type: {}, id: {})"), GetType()._to_string(), _id);
}

UnitId& UnitId::operator=(const UnitId& rhs)
{
    if (this != &rhs)
    {
        _type = rhs._type;
        _id = rhs._id;
    }

    return *this;
}

} // namespace XP