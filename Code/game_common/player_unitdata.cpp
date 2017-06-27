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

PlayerUnitData& PlayerUnitData::operator=(const PlayerUnitData& rhs)
{
    if (this != &rhs)
    {
        _name = rhs._name;
    }

    return *this;
}

PlayerUnitData& PlayerUnitData::operator=(PlayerUnitData&& rhs)
{
    if (this != &rhs)
    {
        _name = std::move(rhs._name);
    }

    return *this;
}

void PlayerUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP
