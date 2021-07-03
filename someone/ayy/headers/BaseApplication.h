#pragma once

#include "AyyImGUI.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math.h"

namespace ayy {

class BaseScene;
class BaseApplication
{
public:
    BaseApplication();
    virtual ~BaseApplication();
    
    bool Setup();
    bool CreateWindow();
    void MainLoop();
    void Cleanup();
    
    void SetScene(BaseScene* scene);// { _runningScene = scene;}
    
protected:
    GLFWwindow* _window = nullptr;
    ImGUIDelegate _imguiDelegate;
    
    BaseScene* _runningScene = nullptr;
};

}

