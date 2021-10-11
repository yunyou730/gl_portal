#pragma once
#include "Ayy.h"

namespace crude
{
class FreeCamera : public ayy::Camera
{
public:
    FreeCamera(int viewportWidth,int viewportHeight);
    void HandleKeyboardInput(GLFWwindow* window,float deltaTime);
    
private:
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
};

}
