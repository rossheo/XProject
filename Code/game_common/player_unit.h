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
    virtual eUnitType GetType() const override { return _unitType; }

    virtual void PostCreate() override;
    virtual void OnCreate() override;

protected:
    virtual void Update(float frame) override;

private:
    const eUnitType _unitType = eUnitType::PLAYER_UNIT;
};

} // namespace XP
