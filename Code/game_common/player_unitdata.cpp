#include "stdafx.h"
#include "player_unitdata.h"

namespace XP
{

PlayerUnitData::PlayerUnitData()
{
}

PlayerUnitData::PlayerUnitData(PlayerUnitData&& playerUnitData)
{
    *this = std::move(playerUnitData);
}

PlayerUnitData::PlayerUnitData(const PlayerUnitData& playerUnitData)
{
    *this = playerUnitData;
}

PlayerUnitData::~PlayerUnitData()
{
}

void PlayerUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP
