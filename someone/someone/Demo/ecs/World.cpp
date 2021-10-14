#include "World.h"
#include "BaseEntity.h"
#include "RenderSystem.h"

namespace crude
{
World::World()
    :_entityIdCounter(0)
{
    
}

World::~World()
{
    CleanUp();
}

BaseEntity* World::CreateEntity()
{
    _entityIdCounter++;
    auto newEntity = new BaseEntity(_entityIdCounter);
    _entityMap.insert(std::make_pair(_entityIdCounter,newEntity));
    return newEntity;
}

void World::DestroyEntity(int uuid)
{
    
}

//void World::Init()
//{
//    
//}

void World::CleanUp()
{
    for(auto it : _updateSystems)
    {
        AYY_SAFE_DEL(it);
    }
    _updateSystems.clear();
    
    for(auto it : _renderSystems)
    {
        AYY_SAFE_DEL(it);
    }
    _renderSystems.clear();
    
    for(auto it : _entityMap)
    {
        AYY_SAFE_DEL(it.second);
    }
    _entityMap.clear();
}


void World::OnUpdate(float deltaTime)
{
    for(auto it : _updateSystems)
    {
        it->OnUpdate(deltaTime);
    }
}

void World::OnRender()
{
    for(auto it : _renderSystems)
    {
        it->OnRender();
    }
}

std::vector<BaseEntity*> World::QueryEntities(const std::vector<ECompType>& comps)
{
    std::vector<BaseEntity*> entities;
    for(auto it : _entityMap)
    {
        if(it.second->QueryComp(comps))
        {
            entities.push_back(it.second);
        }
    }
    return entities;
}

}

