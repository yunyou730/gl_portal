#pragma once
#include "BaseSystem.h"


namespace crude {

class InputSystem : public BaseSystem
{
public:
    InputSystem(World* world);
    
    virtual void OnKeyboardInput(GLFWwindow* window,float deltaTime) override;
    
    virtual void Init() override {}
    virtual void OnUpdate(float deltaTime) override {}
    virtual void Cleanup() override {}    
};

}
