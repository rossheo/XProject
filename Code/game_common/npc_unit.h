#pragma once
#include "actor_unit.h"

namespace XP
{

class NpcUnitData;

class NpcUnit : public ActorUnit
{
public:
    explicit NpcUnit(const UnitId& unitId, const NpcUnitData& npcUnitData);
    virtual ~NpcUnit();

    NpcUnit(const NpcUnit&) = delete;
    NpcUnit& operator= (const NpcUnit&) = delete;

public:
    virtual eUnitType GetType() const override { return _unitType; }

    virtual void PostCreate() override;
    virtual void OnCreate() override;

protected:
    virtual void Update(float frame) override;

private:
    const eUnitType _unitType = eUnitType::NPC_UNIT;
};

} // namespace XP
