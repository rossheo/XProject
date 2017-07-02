#pragma once
#include "actor_unit.h"

namespace XP
{

class NpcUnitData;

class NpcUnit : public ActorUnit
{
public:
    explicit NpcUnit(const NpcUnitData& npcUnitData);
    virtual ~NpcUnit();

    NpcUnit(const NpcUnit&) = delete;
    NpcUnit& operator= (const NpcUnit&) = delete;

public:
    static const eUnitType unitType;
    virtual eUnitType GetType() const override { return unitType; }

    virtual void PostCreate() override;
    virtual void OnCreate() override;

protected:
    virtual void Update(float frame) override;
};

} // namespace XP
