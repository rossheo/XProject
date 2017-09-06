#include "stdafx.h"
#include "unit.h"

namespace XP
{

Unit::Unit()
    : _unitId(UnitId::INVALID)
    , _unitData()
{
}

Unit::~Unit()
{
}

void Unit::SetUnitId(const UnitId& unitId)
{
    if (GetType() == unitId.GetType())
    {
        _unitId = unitId;
        return;
    }

    LOG_ERROR(LOG_FILTER_UNIT, "Unit type is difference. this: {}, param: {}",
        _unitId, unitId);
}

} // namespace XP