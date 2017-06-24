#include "stdafx.h"
#include "unitdata.h"

#include "player_unitdata.h"
#include "npc_unitdata.h"

namespace XP
{

UnitData::UnitData()
{
}

UnitData::~UnitData()
{
}

void UnitData::Clear() noexcept
{
    _upPlayerUnitData.reset();
    _upNpcUnitData.reset();
}

void UnitData::CreatePlayerUnitData(PlayerUnitData&& unitData)
{
    _upPlayerUnitData = std::make_unique<PlayerUnitData>(std::move(unitData));
}

PlayerUnitData* UnitData::GetPlayerUnitData() const
{
    return _upPlayerUnitData.get();
}

void UnitData::SetPlayerUnitData(const PlayerUnitData& unitData)
{
    (*_upPlayerUnitData) = unitData;
}

void UnitData::CreateNpcUnitData(NpcUnitData&& unitData)
{
    _upNpcUnitData = std::make_unique<NpcUnitData>(std::move(unitData));
}

NpcUnitData* UnitData::GetNpcUnitData() const
{
    return _upNpcUnitData.get();
}

void UnitData::SetNpcUnitData(const NpcUnitData& unitData)
{
    (*_upNpcUnitData) = unitData;
}

} // namespace XP