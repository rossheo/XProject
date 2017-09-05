#include "stdafx.h"
#include "unit_lock.h"
#include "player_unit.h"
#include "npc_unit.h"

namespace XP
{

//////////////////////////////////////////////////////////////////////////
UnitLock::UnitLock()
{
}

UnitLock::~UnitLock()
{
}

void UnitLock::SetUnit(const std::initializer_list<UnitId>& unitIds)
{
    _unitIds.clear();

    for (const auto& unitId : unitIds)
    {
        _unitIds.insert(unitId);
    }
}

void UnitLock::SetUnit(const std::initializer_list<std::set<UnitId>>& unitIds)
{
    _unitIds.clear();

    for (const auto& setUnitIds : unitIds)
    {
        for (const auto& unitId : setUnitIds)
        {
            _unitIds.insert(unitId);
        }
    }
}

PlayerUnit* UnitLock::GetPlayerUnit(const UnitId& unitId)
{
    Unit* pUnit = nullptr;

    if (unitId.IsInvalid())
        return nullptr;

    if (eUnitType::PLAYER_UNIT != unitId.GetType()._to_integral())
        return nullptr;

    if (!UnitThreadLocalStorage::Get(unitId, pUnit))
        return nullptr;

    ASSERT(pUnit);

    return static_cast<PlayerUnit*>(pUnit);
}

NpcUnit* UnitLock::GetNpcUnit(const UnitId& unitId)
{
    Unit* pUnit = nullptr;

    if (unitId.IsInvalid())
        return nullptr;

    if (eUnitType::NPC_UNIT != unitId.GetType()._to_integral())
        return nullptr;

    if (!UnitThreadLocalStorage::Get(unitId, pUnit))
        return nullptr;

    return static_cast<NpcUnit*>(pUnit);
}

//////////////////////////////////////////////////////////////////////////
UnitThreadLocalStorage* UnitThreadLocalStorage::_s_pUnitTLS;

bool UnitThreadLocalStorage::Initialize()
{
    if (_s_pUnitTLS)
        return true;

    try
    {
        _s_pUnitTLS = new UnitThreadLocalStorage();
    }
    catch (const std::exception& ex)
    {
        LOG_ERROR(LOG_FILTER_SYSTEM, "{}", ex);
        return false;
    }

    return true;
}

void UnitThreadLocalStorage::Release()
{
    if (_s_pUnitTLS)
    {
        delete _s_pUnitTLS;
        _s_pUnitTLS = nullptr;
    }
}

void UnitThreadLocalStorage::Insert(const UnitId& unitId, Unit* pUnit)
{
    if (!_s_pUnitTLS)
        return;

    _s_pUnitTLS->_units.insert({ unitId, pUnit });
}

void UnitThreadLocalStorage::Remove(const UnitId& unitId)
{
    if (!_s_pUnitTLS)
        return;

    _s_pUnitTLS->_units.erase(unitId);
}

bool UnitThreadLocalStorage::Get(const UnitId& unitId, Unit*& pUnit)
{
    if (!_s_pUnitTLS)
        return false;

    auto it = _s_pUnitTLS->_units.find(unitId);
    if (it != _s_pUnitTLS->_units.end())
    {
        pUnit = it->second;
        return true;
    }

    pUnit = nullptr;
    return false;
}

} // namespace XP
