#include "stdafx.h"
#include "npc_unitdata.h"

namespace XP
{

NpcUnitData::NpcUnitData()
{
}

NpcUnitData::NpcUnitData(NpcUnitData&& npcUnitData)
{
    *this = std::move(npcUnitData);
}

NpcUnitData::NpcUnitData(const NpcUnitData& npcUnitData)
{
    *this = npcUnitData;
}

NpcUnitData::~NpcUnitData()
{
}

void NpcUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP