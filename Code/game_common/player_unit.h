#pragma once
#include "actor_unit.h"

namespace XP
{

class PlayerUnitData;

class PlayerUnit : public ActorUnit
{
public:
    explicit PlayerUnit(const UnitId& unitId, const PlayerUnitData& playerUnitData);
    virtual ~PlayerUnit();

    PlayerUnit(const PlayerUnit&) = delete;
    PlayerUnit& operator= (const PlayerUnit&) = delete;

public:
    static const eUnitType unitType;
    virtual eUnitType GetType() const override { return unitType; }

    virtual void PostCreate() override;
    virtual void OnCreate() override;

    void GetData(PlayerUnitData& playerUnitData);

protected:
    virtual void Update(float frame) override;
};

} // namespace XP
