#include "stdafx.h"
#include "prototype_unitlock.h"
#include "prototype_server_app.h"

namespace XP
{

PrototypeUnitLock::PrototypeUnitLock()
{
}

PrototypeUnitLock::~PrototypeUnitLock()
{
}

void PrototypeUnitLock::Lock()
{
    for (auto unitId : _unitIds)
    {
        SlimRWLock lock;
        Unit* pUnit = nullptr;

        if (!g_UnitManager.GetUnitLockTraits(unitId, lock, pUnit))
            continue;

        ASSERT(pUnit);

        lock.EnterWrite();

        UnitThreadLocalStorage::Insert(unitId, pUnit);
    }
}

void PrototypeUnitLock::UnLock()
{
    for (auto unitId : _unitIds)
    {
        SlimRWLock lock;
        Unit* pUnit = nullptr;

        if (!g_UnitManager.GetUnitLockTraits(unitId, lock, pUnit))
            continue;

        UnitThreadLocalStorage::Remove(unitId);

        lock.LeaveWrite();
    }
}

} // namespace XP
