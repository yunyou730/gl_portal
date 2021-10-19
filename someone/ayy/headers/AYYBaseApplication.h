#pragma once

#include "AyyImGUI.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AYYMath.h"

namespace ayy {

class BaseScene;
class BaseApplication
{
public:
    BaseApplication();
    virtual ~BaseApplication();
    
    bool Setup();
    bool CreateWindow(int width,int height);
    void MainLoop();
    void Cleanup();
    
    void SetScene(BaseScene* scene);
    
    ImGUIDelegate* GetGUIDelegate() { return &_imguiDelegate;}
    
    void GetWindowSize(int& width,int& height);
    void GetFramebufferSize(int& width,int& height);
    
protected:
    void SetupImGUI();
    
protected:
    GLFWwindow*     _window = nullptr;
    ImGUIDelegate   _imguiDelegate;
    BaseScene*      _runningScene = nullptr;
};

}

