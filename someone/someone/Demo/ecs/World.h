#pragma once
#include "Ayy.h"
#include <map>
#include "Define.h"
#include <vector>

namespace crude {

class BaseEntity;
class BaseSystem;
class World
{
public:
    World();
    ~World();
    
    BaseEntity* CreateEntity();
    void DestroyEntity(int uuid);
    
//    void Init();
    void CleanUp();
    
    void OnUpdate(float deltaTime);
    void OnRender();
    
    
    std::vector<BaseEntity*> QueryEntities(const std::vector<ECompType>& comps);
   
    
    template<typename SysClass>
    void RegisterUpdateSystem()
    {
        BaseSystem* sys = new SysClass(this);
        _updateSystems.push_back(sys);
    }
    
    template<typename SysClass>
    void RegisterRenderSystem()
    {
        BaseSystem* sys = new SysClass(this);
        _renderSystems.push_back(sys);
    }
    
protected:
    EntityID _entityIdCounter = 0;
    std::map<EntityID,BaseEntity*> _entityMap;
    std::vector<BaseSystem*>    _updateSystems;
    std::vector<BaseSystem*>    _renderSystems;
};

}

