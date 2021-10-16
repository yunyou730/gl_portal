#pragma once
#include "Ayy.h"
#include <map>
#include "Define.h"
#include <vector>
#include <map>
#include "BaseSystem.h"

namespace crude {

class BaseEntity;
class SingletonComponent;
class World
{
public:
    World();
    ~World();
    
    BaseEntity* CreateEntity();
    void DestroyEntity(int uuid);
    
    void CleanUp();
    
    void OnUpdate(float deltaTime);
    void OnRender();
    void OnKeyboardInput(GLFWwindow* window,float deltaTime);
    
    std::vector<BaseEntity*> QueryEntities(const std::vector<ECompType>& comps);
    
    template<typename SysClass>
    void RegisterUpdateSystem()
    {
        BaseSystem* sys = new SysClass(this);
        sys->Init();
        _updateSystems.push_back(sys);
    }
    
    template<typename SysClass>
    void RegisterRenderSystem()
    {
        BaseSystem* sys = new SysClass(this);
        sys->Init();
        _renderSystems.push_back(sys);
    }
    
    template<typename SysClass>
    void RegisterInputSystem()
    {
        BaseSystem* sys = new SysClass(this);
        sys->Init();
        _inputSystems.push_back(sys);
    }
    
    template<typename SingletonClass>
    SingletonClass* GetSingleton(ESingleton singletonType)
    {
        auto it = _singletons.find(singletonType);
        if(it != _singletons.end())
        {
            return dynamic_cast<SingletonClass*>(it->second);
        }
        return nullptr;
    }
    
    template<ESingleton singletonType,typename SingletonClass>
    SingletonClass* RegisterSingleton()
    {
        auto instance = new SingletonClass();
        _singletons.insert(std::make_pair(singletonType,instance));
        return instance;
    }
    
protected:
    void ClearSystems();
    void ClearEntities();
    void ClearSingletons();
    
protected:
    EntityID _entityIdCounter = 0;
    std::map<EntityID,BaseEntity*> _entityMap;
    
    std::vector<BaseSystem*>    _updateSystems;
    std::vector<BaseSystem*>    _renderSystems;
    std::vector<BaseSystem*>    _inputSystems;
    
    std::map<ESingleton,SingletonComponent*>   _singletons;
};

}

