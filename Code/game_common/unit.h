#pragma once
#include "unit_id.h"
#include "unitdata.h"

namespace XP
{

class Unit
{
public:
    explicit Unit();
    virtual ~Unit();

public:
    virtual eUnitType GetType() const = 0;

    void SetUnitId(const UnitId& unitId);
    const UnitId& GetUnitId() const { return _unitId; }

protected:
    UnitData _unitData;

private:
    UnitId _unitId;
};

} // namespace XP
