#include "FreeCamera.h"

namespace crude {

FreeCamera::FreeCamera(int viewportWidth,int viewportHeight)
    :ayy::Camera(viewportWidth, viewportHeight)
{
    
}

void FreeCamera::HandleKeyboardInput(GLFWwindow* window,float deltaTime)
{
    // handle camera move
    float delta = deltaTime * _camMoveSpeed;
    float deltaRot = deltaTime * _camRotSpeed;
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = delta * GetLookDir();
        TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = -delta * GetLookDir();
        TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = -delta * GetRightDir();
        TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = delta * GetRightDir();
        TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        TakeYaw(-deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        TakeYaw(deltaRot);
    }
    
    // camera rotate
    delta = _camRotSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        TakePitch(-deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        TakePitch(deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        TakeYaw(-deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        TakeYaw(deltaRot);
    }
    
    
}

}
