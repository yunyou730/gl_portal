#pragma once
#include "Ayy.h"

namespace crude
{
class FreeCamera : public ayy::Camera
{
public:
    FreeCamera(int viewportWidth,int viewportHeight);
    void HandleKeyboardInput(GLFWwindow* window,float deltaTime);
    
    void SetMoveSpeed(float moveSpeed) { _camMoveSpeed = moveSpeed; }
    void SetRotSpeed(float rotSpeed) {_camRotSpeed = rotSpeed;}
    
private:
    float   _camMoveSpeed   = 12.0f;
    float   _camRotSpeed    = 40;
};

}
