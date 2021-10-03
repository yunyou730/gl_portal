#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace df {
class GLView
{
public:
    GLView();
    ~GLView();
    
    static void InitEnv();
    
    bool ShouldClose();
    void PollEvents();
    void OnRenderEnd();
    
    int Width() const { return _width;}
    int Height() const { return _height;}
    
protected:
    void CreateWindow();
    
protected:
    
    GLFWwindow* _window = nullptr;
    
    int _width = 320;
    int _height = 480;
};
}
