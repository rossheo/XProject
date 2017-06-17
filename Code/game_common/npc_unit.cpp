#include "stdafx.h"
#include "npc_unit.h"
#include "npc_unitdata.h"

namespace XP
{
NpcUnit::NpcUnit(const UnitId& unitId, const NpcUnitData& npcUnitData)
{
    SetUnitId(unitId);
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