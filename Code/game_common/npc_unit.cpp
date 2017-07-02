#include "stdafx.h"
#include "npc_unit.h"
#include "npc_unitdata.h"

namespace XP
{
const eUnitType NpcUnit::unitType = eUnitType::NPC_UNIT;

NpcUnit::NpcUnit(const NpcUnitData& npcUnitData)
{
    SetUnitId(npcUnitData.GetUnitId());
    _unitData.CreateNpcUnitData(NpcUnitData(npcUnitData));
}

NpcUnit::~NpcUnit()
{
}

void NpcUnit::PostCreate()
{
}

void NpcUnit::OnCreate()
{
}

void NpcUnit::Update(float frame)
{
    UNREFERENCED_PARAMETER(frame);
}

} // namespace XP