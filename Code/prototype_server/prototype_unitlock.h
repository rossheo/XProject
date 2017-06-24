#pragma once
#include "unit_lock.h"

namespace XP
{

class PrototypeUnitLock : public UnitLock
{
public:
    explicit PrototypeUnitLock();
    ~PrototypeUnitLock();

    virtual void Lock();
    virtual void UnLock();
};

} // namespace XP