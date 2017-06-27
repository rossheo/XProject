#pragma once

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

public:
    void SetName(const std::wstring& name);
    std::wstring GetName() const { return _name; }

private:
    std::wstring _name;
};

} // namespace XP