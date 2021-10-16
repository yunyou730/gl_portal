#pragma once
#include "BaseSystem.h"

namespace crude {

class CameraSingleton;
class RenderSystem : public BaseSystem
{
public:
    RenderSystem(World* world);
    
    virtual void Init() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender() override;
    virtual void Cleanup() override;
    
protected:
    CameraSingleton* _camera = nullptr;
};

}
