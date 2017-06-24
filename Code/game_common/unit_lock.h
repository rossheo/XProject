#pragma once
#include "unit_id.h"

namespace XP
{

class Unit;
class PlayerUnit;
class NpcUnit;

class UnitLock
{
public:
    explicit UnitLock();
    ~UnitLock();

    void SetUnit(std::initializer_list<UnitId> unitIds);

    virtual void Lock() = 0;
    virtual void UnLock() = 0;

    static PlayerUnit* GetPlayerUnit(const UnitId& unitId);
    static NpcUnit* GetNpcUnit(const UnitId& unitId);

protected:
    std::set<UnitId> _unitIds;
};

template <typename TUnitLock>
class UnitScopeLock
{
public:
    explicit UnitScopeLock(std::initializer_list<UnitId> unitIds);
    ~UnitScopeLock();

private:
    TUnitLock _lock;
};

template <typename TUnitLock>
UnitScopeLock<TUnitLock>::UnitScopeLock(std::initializer_list<UnitId> unitIds)
{
    _lock.SetUnit(unitIds);

    _lock.Lock();
}

template <typename TUnitLock>
UnitScopeLock<TUnitLock>::~UnitScopeLock()
{
    _lock.UnLock();
}

//////////////////////////////////////////////////////////////////////////
class UnitThreadLocalStorage
{
public:
    explicit UnitThreadLocalStorage() {}
    ~UnitThreadLocalStorage() {}

    UnitThreadLocalStorage(const UnitThreadLocalStorage&) = delete;
    UnitThreadLocalStorage& operator= (const UnitThreadLocalStorage&) = delete;

public:
    static bool Initialize();
    static void Release();

    static void Insert(const UnitId& unitId, Unit* pUnit);
    static void Remove(const UnitId& unitId);
    static bool Get(const UnitId& unitId, Unit*& pUnit);

private:
    __declspec(thread) static UnitThreadLocalStorage* _s_pUnitTLS;

    std::unordered_map<UnitId, Unit*> _units;
};

} // namespace XP
