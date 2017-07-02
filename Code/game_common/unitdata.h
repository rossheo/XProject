#pragma once
#include "player_unitdata.h"
#include "npc_unitdata.h"

namespace XP
{

class UnitData
{
public:
    explicit UnitData();
    ~UnitData();

    UnitData(const UnitData&) = delete;
    UnitData& operator= (const UnitData&) = delete;

public:
    void CreatePlayerUnitData(PlayerUnitData&& unitData);
    bool IsPlayerUnitData() const;
    bool GetPlayerUnitData(PlayerUnitData*& pUnitData);
    const PlayerUnitData& GetPlayerUnitData() const;

    void CreateNpcUnitData(NpcUnitData&& unitData);
    bool IsNpcUnitData() const;
    bool GetNpcUnitData(NpcUnitData*& pUnitData);
    const NpcUnitData& GetNpcUnitData() const;

private:
    boost::variant<PlayerUnitData, NpcUnitData> _data;
};

} // namespace XP