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

void NpcUnitData::To(pb_prototype::NPCUnitData& pbUnitData)
{
    pbUnitData.set_unit_type(_unitId.GetType());
    pbUnitData.set_unit_id(_unitId.GetId());
    pbUnitData.set_name(ToUTF8(_name));
}

void NpcUnitData::From(const pb_prototype::NPCUnitData& pbUnitData)
{
    UnitId fromUnitId(eUnitType::_from_integral(pbUnitData.unit_type()), pbUnitData.unit_id());
    ASSERT(_unitId == fromUnitId);

    _name = FromUTF8(pbUnitData.name());
}

void NpcUnitData::SetUnitId(const UnitId& unitId)
{
    _unitId = unitId;
}

UnitId NpcUnitData::GetUnitId() const
{
    return _unitId;
}

void NpcUnitData::SetName(const std::wstring& name)
{
    _name = name;
}

} // namespace XP