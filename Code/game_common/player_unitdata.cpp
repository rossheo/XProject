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

void PlayerUnitData::To(prototype::PlayerUnitData& pbUnitData)
{
    pbUnitData.set_name(ToUTF8(_name));
}

void PlayerUnitData::From(const prototype::PlayerUnitData& pbUnitData)
{
    _name = FromUTF8(pbUnitData.name());
}

void PlayerUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP
