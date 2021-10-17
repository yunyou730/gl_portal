#pragma once
#include "BaseSystem.h"


namespace crude {
class SpawnSingleton;
struct SpawnParam;
class SpawnSystem : public BaseSystem
{
public:
    SpawnSystem(World* world);
    
    virtual void Init() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender() override;
    virtual void Cleanup() override;
    
protected:
    void DoSpawn(SpawnParam*);
    
    void SpawnBlock(SpawnParam*);
protected:
    SpawnSingleton* _spawn;
};

}
