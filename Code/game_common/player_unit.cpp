#include "stdafx.h"
#include "player_unit.h"
#include "player_unitdata.h"

namespace XP
{
const eUnitType PlayerUnit::unitType = eUnitType::PLAYER_UNIT;

PlayerUnit::PlayerUnit(const UnitId& unitId, const PlayerUnitData& playerUnitData)
{
    SetUnitId(unitId);
    _unitData.CreatePlayerUnitData(PlayerUnitData(playerUnitData));
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::Initialize()
{
}

void PlayerUnit::PostCreate()
{
}

void PlayerUnit::OnCreate()
{
}

void PlayerUnit::GetData(PlayerUnitData& unitData) const
{
    if (auto pUnitData = _unitData.GetPlayerUnitData())
    {
        unitData = *pUnitData;
    }
}

void PlayerUnit::SetData(const PlayerUnitData& unitData)
{
    _unitData.SetPlayerUnitData(unitData);
}

void PlayerUnit::SetName(const std::wstring& name)
{
    PlayerUnitData unitData;
    GetData(unitData);

    unitData.SetName(name);

    SetData(unitData);
}

std::wstring PlayerUnit::GetName() const
{
    PlayerUnitData unitData;
    GetData(unitData);

    return unitData.GetName();
}

void PlayerUnit::Update(float frame)
{
    UNREFERENCED_PARAMETER(frame);
}

} // namespace XP
