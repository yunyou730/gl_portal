#pragma once
#include "BaseSystem.h"


namespace crude {

class RenderSystem : public BaseSystem
{
public:
    RenderSystem(World* world);
    
    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void OnRender() override;
    virtual void Cleanup() override;
};

}
