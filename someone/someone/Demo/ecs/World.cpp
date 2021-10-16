#include "World.h"
#include "BaseEntity.h"
#include "RenderSystem.h"
#include "SingletonComponent.h"

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

void World::CleanUp()
{
    ClearSystems();
    ClearEntities();
    ClearSingletons();
}

void World::ClearEntities()
{
    for(auto it : _entityMap)
    {
        AYY_SAFE_DEL(it.second);
    }
    _entityMap.clear();
}

void World::ClearSystems()
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
}

void World::ClearSingletons()
{
    for(auto it : _singletons)
    {
        delete it.second;
    }
    _singletons.clear();
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

void World::OnKeyboardInput(GLFWwindow* window,float deltaTime)
{
    for(auto it : _inputSystems)
    {
        it->OnKeyboardInput(window,deltaTime);
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

