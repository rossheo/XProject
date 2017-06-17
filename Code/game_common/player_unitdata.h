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

    PlayerUnitData& operator= (const PlayerUnitData& rhs)
    {
        if (this != &rhs)
        {
            _name = rhs._name;
        }

        return *this;
    }

    PlayerUnitData& operator= (PlayerUnitData&& rhs)
    {
        if (this != &rhs)
        {
            _name = std::move(rhs._name);
        }

        return *this;
    }

public:
    void SetName(const std::wstring& name);
    std::wstring GetName() const { return _name; }

private:
    std::wstring _name;
};

} // namespace XP