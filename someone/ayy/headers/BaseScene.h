#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ayy {
class BaseScene
{
public:
    BaseScene() {}
    BaseScene(int viewportWidth,int viewportHeight);
    virtual ~BaseScene() {}
    
    virtual void Prepare() = 0;
    virtual void Cleanup() = 0;
    virtual void OnRender() = 0;
    
    virtual void OnUpdate();
    virtual void HandleKeyboardInput(GLFWwindow* window);
    
    void SetDeltaTime(float deltaTime) {_deltaTimeThisFrame = deltaTime;}
    float GetDeltaTime() const { return _deltaTimeThisFrame;}
    
    int GetViewportWidth() const { return _viewportWidth;}
    int GetViewportHeight() const { return _viewportHeight;}
    
    virtual void OnViewportSizeChanged(int width,int height);
    
protected:
    float   _deltaTimeThisFrame = 0.0f;
    int     _viewportWidth,_viewportHeight;
    
};

}
