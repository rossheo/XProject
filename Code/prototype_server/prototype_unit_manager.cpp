#include "stdafx.h"
#include "prototype_unit_manager.h"

namespace XP
{

PrototypeUnitManager::PrototypeUnitManager()
    : UnitManager()
{
}

PrototypeUnitManager::~PrototypeUnitManager()
{
}

bool PrototypeUnitManager::GetUnitLockTraits(UnitId unitId, SlimRWLock& lock, Unit*& pUnit)
{
    auto it = _s_concurrent_units.find(unitId);
    if (it == _s_concurrent_units.end())
        return false;

    UnitLockTraits& unitLockTraits = it->second;
    lock = *(std::get<0>(unitLockTraits).get());
    pUnit = std::get<1>(unitLockTraits);

    return true;
}

} // namespace XP