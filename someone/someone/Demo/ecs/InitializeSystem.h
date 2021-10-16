#pragma once
#include "BaseSystem.h"

namespace crude {

class SpawnSingleton;
class MapSingleton;
class InitializeSystem : public BaseSystem
{
public:
    InitializeSystem(World* world);
    
    virtual void Init() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender() override;
    virtual void Cleanup() override;
    
protected:
    MapSingleton* _map = nullptr;
    SpawnSingleton* _spawn = nullptr;
};

}
