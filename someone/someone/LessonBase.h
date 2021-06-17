#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class LessonBase
{
public:
    virtual ~LessonBase() {}
    
    virtual void Prepare() = 0;
    virtual void Cleanup() = 0;
    virtual void OnRender(float deltaTime) = 0;
    
    virtual void OnUpdate();
    virtual void HandleKeyboardInput(GLFWwindow* window);
    
    void SetDeltaTime(float deltaTime) {_deltaTimeThisFrame = deltaTime;}
    float GetDeltaTime() const { return _deltaTimeThisFrame;}
protected:
    float   _deltaTimeThisFrame = 0.0f;
};
