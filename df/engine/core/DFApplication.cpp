#include "DFApplication.h"
#include <cstdio>
#include "DFGLView.h"
#include "DFRenderer.h"
#include "DFMacro.hpp"
#include <thread>

#include "../ecs/DFWorld.h"

namespace df {


Application* Application::s_instance = nullptr;

Application::Application()
{
    s_instance = this;
}

Application::~Application()
{
    s_instance = nullptr;
}

void Application::Run()
{
    DidFinishLaunching();
    MainLoop();
    CleanUp();
}

void Application::MainLoop()
{
    while(!_view->ShouldClose())
    {
        CalcDeltaTime();
        
        float frameBeginTime = _view->GetTime();
        
        // update
        _world->OnTick(_deltaTime);
        
        // do render
        _renderer->Clear(_view);
        _renderer->Render();
        
        // gl view
        _view->OnRenderEnd();
        _view->PollEvents();
        _view->RefreshLastFrameTime();
        
        
        // 
        
        // sleep for FPS
        float frameEndTime = _view->GetTime();
        float realDeltaTime = frameEndTime - frameBeginTime;
        float desireDeltaTime = GetDesireDeltaTime();
        if(realDeltaTime < desireDeltaTime)
        {
            float sleepTime = desireDeltaTime - realDeltaTime;
//            printf("%.3f\n",sleepTime);
            std::chrono::milliseconds ms = std::chrono::milliseconds(static_cast<int>(sleepTime * 1000));
            std::this_thread::sleep_for(ms);
        }
    }
}


void Application::DidFinishLaunching()
{
    _view = new GLView();
    _renderer = new Renderer();
    _renderer->SetClearColor(Color4F(0.3f,0.5f,1.0f,1.0f));
    
    _world = new df::ecs::World();
    _world->Init();
}

void Application::DidEnterBackground()
{
    
}

void Application::DidEnterForeground()
{
    
}

void Application::CleanUp()
{
    DF_SAFE_DEL(_view);
    DF_SAFE_DEL(_renderer);
    DF_SAFE_DEL(_world);
}

void Application::CalcDeltaTime()
{
    _deltaTime = _view->GetTime() - _view->GetLastFrameTime();
//    printf("dt %.3f\n",_deltaTime);
}

float Application::GetDesireDeltaTime() const
{
    return 1.0/_desireFPS;
}


}
