#pragma once
#include "game_unit.h"

namespace XP
{

class ActorUnit : public GameUnit
{
public:
    explicit ActorUnit();
    virtual ~ActorUnit();

    ActorUnit(const ActorUnit&) = delete;
    ActorUnit& operator= (const ActorUnit&) = delete;

public:
    virtual eUnitType GetType() const override = 0;

    virtual void Initialize();
    virtual void PostCreate();
    virtual void OnCreate() = 0;
};

} // namespace XP