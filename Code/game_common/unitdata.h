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

    void CreatePlayerUnitData(PlayerUnitData&& playerUnitData);
    PlayerUnitData* GetPlayerUnitData() const { return _upPlayerUnitData.get(); }

    void CreateNpcUnitData(NpcUnitData&& npcUnitData);
    NpcUnitData* GetNpcUnitData() const { return _upNpcUnitData.get(); }

private:
    std::unique_ptr<PlayerUnitData> _upPlayerUnitData;
    std::unique_ptr<NpcUnitData> _upNpcUnitData;
};

} // namespace XP