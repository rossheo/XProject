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

void UnitData::CreatePlayerUnitData(PlayerUnitData&& unitData)
{
    _data = unitData;
}

bool UnitData::IsPlayerUnitData() const
{
    const PlayerUnitData* pUnitData = boost::get<PlayerUnitData>(&_data);
    if (!pUnitData)
        return false;

    return true;
}

bool UnitData::GetPlayerUnitData(PlayerUnitData*& pUnitData)
{
    if (!IsPlayerUnitData())
        return false;

    pUnitData = boost::get<PlayerUnitData>(&_data);
    return true;
}

const PlayerUnitData& UnitData::GetPlayerUnitData() const
{
    if (!IsPlayerUnitData())
    {
        ASSERT(false);
    }

    return boost::get<PlayerUnitData>(_data);
}

void UnitData::CreateNpcUnitData(NpcUnitData&& unitData)
{
    _data = unitData;
}

bool UnitData::IsNpcUnitData() const
{
    const NpcUnitData* pUnitData = boost::get<NpcUnitData>(&_data);
    if (!pUnitData)
        return false;

    return true;
}

bool UnitData::GetNpcUnitData(NpcUnitData*& pUnitData)
{
    if (!IsNpcUnitData())
        return false;

    pUnitData = boost::get<NpcUnitData>(&_data);
    return true;
}

const NpcUnitData& UnitData::GetNpcUnitData() const
{
    if (!IsNpcUnitData())
    {
        ASSERT(false);
    }

    return boost::get<NpcUnitData>(_data);
}

} // namespace XP