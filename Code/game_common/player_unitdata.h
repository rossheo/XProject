#pragma once
#include "unit_id.h"
#include "prototype_common.pb.h"

namespace XP
{

class PlayerUnitData
{
public:
    explicit PlayerUnitData();
    explicit PlayerUnitData(const PlayerUnitData& playerUnitData);
    explicit PlayerUnitData(PlayerUnitData&& playerUnitData);
    ~PlayerUnitData();

    PlayerUnitData& operator= (const PlayerUnitData& rhs);
    PlayerUnitData& operator= (PlayerUnitData&& rhs);

    void To(pb_prototype::PlayerUnitData& pbUnitData);
    void From(const pb_prototype::PlayerUnitData& pbUnitData);

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