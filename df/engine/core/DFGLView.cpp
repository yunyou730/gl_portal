#include "DFGLView.h"
#include <iostream>

namespace df {
GLView::GLView()
{
    GLView::InitEnv();
    CreateWindow();
    
    _timeLastFrame = GetTime();
}

GLView::~GLView()
{
    glfwDestroyWindow(_window);
    _window = nullptr;
    glfwTerminate();
}

void GLView::InitEnv()
{
    static bool s_hasInit = false;
    if(!s_hasInit)
    {
        s_hasInit = true;
        
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        
    }
}

void GLView::CreateWindow()
{
    _window = glfwCreateWindow(640, 384, "title", nullptr,nullptr);
    
    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

bool GLView::ShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void GLView::PollEvents()
{
    glfwPollEvents();
}

void GLView::OnRenderEnd()
{
    glfwSwapBuffers(_window);
}

double GLView::GetTime() const
{
    return glfwGetTime();
}

void GLView::RefreshLastFrameTime()
{
    _timeLastFrame = GetTime();
}

}

