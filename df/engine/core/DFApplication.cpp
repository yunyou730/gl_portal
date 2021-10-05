#include "DFApplication.h"
#include <cstdio>
#include "DFGLView.h"
#include "DFRenderer.h"
#include "DFMacro.hpp"
#include <thread>

namespace df {

Application::Application()
{
    
}

Application::~Application()
{
    
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
        
        _renderer->Clear(_view);
        _renderer->Render();
        
        _view->OnRenderEnd();
        _view->PollEvents();
        _view->RefreshLastFrameTime();
        
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
}

void Application::CalcDeltaTime()
{
    _deltaTime = _view->GetTime() - _view->GetLastFrameTime();
    printf("dt %.3f\n",_deltaTime);
}

float Application::GetDesireDeltaTime() const
{
    return 1.0/_desireFPS;
}


}
