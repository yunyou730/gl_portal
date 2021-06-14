#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class LessonBase
{
public:
    virtual ~LessonBase() {}
    
    virtual void Prepare() = 0;
    virtual void Cleanup() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    
    
    virtual void HandleKeyboardInput(GLFWwindow* window);
};
