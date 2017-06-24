#pragma once

namespace XP
{

class PlayerUnitData;
class NpcUnitData;

class UnitData
{
public:
    explicit UnitData();
    ~UnitData();

    UnitData(const UnitData&) = delete;
    UnitData& operator= (const UnitData&) = delete;

public:
    void Clear() noexcept;

    void CreatePlayerUnitData(PlayerUnitData&& unitData);
    PlayerUnitData* GetPlayerUnitData() const;
    void SetPlayerUnitData(const PlayerUnitData& unitData);

    void CreateNpcUnitData(NpcUnitData&& unitData);
    NpcUnitData* GetNpcUnitData() const;
    void SetNpcUnitData(const NpcUnitData& unitData);

private:
    std::unique_ptr<PlayerUnitData> _upPlayerUnitData;
    std::unique_ptr<NpcUnitData> _upNpcUnitData;
};

} // namespace XP