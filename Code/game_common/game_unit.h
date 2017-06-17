#pragma once
#include "unit.h"

namespace XP
{
class GameUnit : public Unit
{
public:
    explicit GameUnit();
    virtual ~GameUnit();

    GameUnit(const GameUnit&) = delete;
    GameUnit& operator= (const GameUnit&) = delete;

public:
    virtual eUnitType GetType() const override = 0;

    virtual void PostCreate() = 0;
    virtual void OnCreate() = 0;

protected:
    virtual void Update(float frame) = 0;
};

} // namespace XP