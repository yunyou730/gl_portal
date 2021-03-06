#include "AYYBaseApplication.h"
#include "AYYBaseScene.h"
#include "../headers/AssetCache/AyyBuiltinMeshFactory.h"

ayy::BaseApplication*    g_app = nullptr;

namespace ayy {


static void framebuffer_size_callback(GLFWwindow* window,int width,int height);
static void processInput(GLFWwindow *window);
static void glfw_error_callback(int error, const char* description);

static BaseScene* s_scene = nullptr;


BaseApplication::BaseApplication()
{
    printf("-------------------------\n");
    printf("Welcome to ayy\n");
    printf("-------------------------\n");
    
    assert(g_app == nullptr);
    g_app = this;
}

BaseApplication::~BaseApplication()
{
    
}

void BaseApplication::SetScene(BaseScene* scene)
{
    _runningScene = scene;
    s_scene = scene;
}

bool BaseApplication::Setup()
{
    // init glfw
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit())
    {
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    // create window with glfw
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);
    
    return true;
}

bool BaseApplication::CreateWindow(int width,int height)
{
    _window = glfwCreateWindow(width, height, "ayy730", NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    // enable glad
    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glfwSetFramebufferSizeCallback(_window,framebuffer_size_callback);
    
    // imgui
    _imguiDelegate.Setup(_window,"#version 330 core");
    

    SetupManagers();
    
    return true;
}

void BaseApplication::MainLoop()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    static double lastFrameTime = glfwGetTime();
    
    while(!glfwWindowShouldClose(_window))
    {
        // Render code here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // render begin
        
        double curTime = glfwGetTime();
        float deltaTime = curTime - lastFrameTime;
        
        if(_runningScene != nullptr)
        {
            _runningScene->SetDeltaTime(deltaTime);
        }
        lastFrameTime = curTime;
        
        // 3D Render logic
        if(_runningScene != nullptr)
        {
            _runningScene->OnUpdate();
            _runningScene->OnRender();
        }
        
        // ImGUI
        _imguiDelegate.OnFrameBegin();
        if(_runningScene != nullptr)
        {
            _runningScene->OnGUI();
        }
        _imguiDelegate.Render();
        _imguiDelegate.OnFrameEnd();
        
        // Render end
        glfwSwapBuffers(_window);
        glfwPollEvents();
        
        // frame logic
        processInput(_window);
    }
}

void BaseApplication::Cleanup()
{
    _imguiDelegate.Destroy();
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void BaseApplication::GetWindowSize(int& width,int& height)
{
    
}

void BaseApplication::GetFramebufferSize(int& width,int& height)
{
    glfwGetFramebufferSize(_window,&width,&height);
}


void BaseApplication::SetupManagers()
{
    _builtinMeshFactory = new ayy::BuiltinMeshFactory();
    _builtinMeshFactory->Init();
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    if(s_scene != nullptr)
    {
        s_scene->OnViewportSizeChanged(width,height);
    }
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    
    if(s_scene != nullptr)
    {
        s_scene->HandleKeyboardInput(window);
    }
}

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

}
