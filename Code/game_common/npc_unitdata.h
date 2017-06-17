#pragma once

namespace XP
{

class NpcUnitData
{
public:
    explicit NpcUnitData();
    explicit NpcUnitData(const NpcUnitData& npcUnitData);
    explicit NpcUnitData(NpcUnitData&& npcUnitData);
    ~NpcUnitData();

    NpcUnitData& operator= (const NpcUnitData& rhs)
    {
        if (this != &rhs)
        {
            _name = rhs._name;
        }

        return *this;
    }

    NpcUnitData& operator= (NpcUnitData&& rhs)
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
