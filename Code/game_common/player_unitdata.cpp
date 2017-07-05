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

void PlayerUnitData::To(pb_prototype::PlayerUnitData& pbUnitData) const
{
    auto& pbUnitId = *pbUnitData.mutable_unit_id();
    _unitId.To(pbUnitId);

    pbUnitData.set_name(ToUTF8(_name));
}

void PlayerUnitData::From(const pb_prototype::PlayerUnitData& pbUnitData)
{
    ASSERT(eUnitType::PLAYER_UNIT == pbUnitData.unit_id().unit_type());

    _unitId.From(pbUnitData.unit_id());
    _name = FromUTF8(pbUnitData.name());
}

void PlayerUnitData::SetUnitId(const UnitId& unitId)
{
    _unitId = unitId;
}

UnitId PlayerUnitData::GetUnitId() const
{
    return _unitId;
}

void PlayerUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP
