#pragma once
#include "unit_manager.h"

namespace XP
{

class PrototypeUnitManager : public UnitManager
{
public:
    explicit PrototypeUnitManager();
    virtual ~PrototypeUnitManager();

public:
    bool GetUnitLockTraits(UnitId unitId, SlimRWLock& lock, Unit*& pUnit);
};

} // namespace XP
