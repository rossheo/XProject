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

void UnitData::CreatePlayerUnitData(PlayerUnitData&& playerUnitData)
{
    _upPlayerUnitData = std::make_unique<PlayerUnitData>(std::move(playerUnitData));
}

void UnitData::CreateNpcUnitData(NpcUnitData&& npcUnitData)
{
    _upNpcUnitData = std::make_unique<NpcUnitData>(std::move(npcUnitData));
}

} // namespace XP