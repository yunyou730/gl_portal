#pragma once
#include "Ayy.h"
#include <vector>

namespace crude
{
class FreeCamera;
class Ground;
class Wall;
class World;
}

class Crude2 : public ayy::BaseScene
{
public:
    Crude2(int viewportWidth,int viewportHeight);
    ~Crude2();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void InitMap();
    void InitGround();
    ayy::Camera* InitMainCamera();
    void InitWall();
    void InitSkyBox();
    void InitModel();
    
protected:
    crude::World*           _world = nullptr;
};
