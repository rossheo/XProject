#pragma once
#include "unit_id.h"
#include "prototype_common.pb.h"

namespace XP
{

class NpcUnitData
{
public:
    explicit NpcUnitData();
    explicit NpcUnitData(const NpcUnitData& npcUnitData);
    explicit NpcUnitData(NpcUnitData&& npcUnitData);
    ~NpcUnitData();

    NpcUnitData& operator= (const NpcUnitData& rhs);
    NpcUnitData& operator= (NpcUnitData&& rhs);

    void To(prototype::NPCUnitData& pbUnitData);
    void From(const prototype::NPCUnitData& pbUnitData);

public:
    void SetUnitId(const UnitId& unitId);
    UnitId GetUnitId() const;

    void SetName(const std::wstring& name);
    std::wstring GetName() const { return _name; }

private:
    UnitId _unitId;
    std::wstring _name;
};

} // namespace XP
