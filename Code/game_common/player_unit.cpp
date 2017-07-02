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

void PlayerUnit::SetName(const std::wstring& name)
{
    PlayerUnitData* pUnitData;
    if (!_unitData.GetPlayerUnitData(pUnitData))
    {
        ASSERT(false);
        return;
    }

    pUnitData->SetName(name);
}

std::wstring PlayerUnit::GetName() const
{
    return _unitData.GetPlayerUnitData().GetName();
}

void PlayerUnit::Update(float frame)
{
    UNREFERENCED_PARAMETER(frame);
}

} // namespace XP
