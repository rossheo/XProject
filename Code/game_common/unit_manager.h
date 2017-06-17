#pragma once
#include "unit_id.h"
#include "id_pool.h"

namespace XP
{

class Unit;
class NpcUnit;
class NpcUnitData;
class PlayerUnit;
class PlayerUnitData;

class UnitManager
{
public:
    typedef IdPool<uint32, UnitId::MIN_ID_VALUE, UnitId::MAX_ID_VALUE> TIdPool;

public:
    explicit UnitManager();
    virtual ~UnitManager();

public:
    PlayerUnit* CreatePlayerUnit(PlayerUnitData&& playerUnitData);
    NpcUnit* CreateNpcUnit(const NpcUnitData& npcUnitData);
    void ReleaseUnit(Unit* pUnit);

private:
    void ReleasePlayerUnit(PlayerUnit* pPlayerUnit);
    void ReleaseNpcUnit(NpcUnit* pNpcUnit);

protected:
    TIdPool _playerIdPool;
    TIdPool _npcIdPool;

    boost::object_pool<PlayerUnit> _playerUnitPool;
    boost::object_pool<NpcUnit> _npcUnitPool;

    SlimRWLock _lock;
};

} // namespace XP