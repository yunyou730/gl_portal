#pragma once
#include "Ayy.h"

namespace crude {
class World;
class BaseSystem
{
public:
    BaseSystem(World* world);
    virtual ~BaseSystem(){}
    
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Cleanup() = 0;
    
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnKeyboardInput(GLFWwindow* window,float deltaTime) {}
    
    World* GetWorld() { return _world;}
protected:
    World*  _world = nullptr;
};
}

