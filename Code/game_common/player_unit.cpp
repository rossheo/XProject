#include "stdafx.h"
#include "player_unit.h"
#include "player_unitdata.h"

namespace XP
{
PlayerUnit::PlayerUnit(const UnitId& unitId, const PlayerUnitData& playerUnitData)
{
    SetUnitId(unitId);
    _unitData.CreatePlayerUnitData(PlayerUnitData(playerUnitData));
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::PostCreate()
{
}

void PlayerUnit::OnCreate()
{
}

void PlayerUnit::Update(float frame)
{
    UNREFERENCED_PARAMETER(frame);
}

} // namespace XP
