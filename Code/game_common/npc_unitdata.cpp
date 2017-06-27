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

NpcUnitData& NpcUnitData::operator=(const NpcUnitData& rhs)
{
    if (this != &rhs)
    {
        _name = rhs._name;
    }

    return *this;
}

NpcUnitData& NpcUnitData::operator=(NpcUnitData&& rhs)
{
    if (this != &rhs)
    {
        _name = std::move(rhs._name);
    }

    return *this;
}

void NpcUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP