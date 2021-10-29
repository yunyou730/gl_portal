#include "InitializeSystem.h"
#include "BaseEntity.h"
#include "World.h"
#include "MapSingleton.h"
#include "SpawnSingleton.h"

namespace crude {

InitializeSystem::InitializeSystem(World* world)
    :BaseSystem(world)
{
    
}

void InitializeSystem::Init()
{
    _map = _world->GetSingleton<MapSingleton>(ESingleton::ST_Map);
    _spawn = _world->GetSingleton<SpawnSingleton>(ESingleton::ST_Spawn);
    if(_map != nullptr && _spawn != nullptr)
    {
        for(auto it : _map->_presetRecords)
        {
            _spawn->AddSpawnData(SpawnParam(it->actorType,it->row,it->col));
        }
    }
}

void InitializeSystem::OnUpdate(float deltaTime)
{
    
}

void InitializeSystem::OnRender()
{
    
}

void InitializeSystem::Cleanup()
{
    
}

}
