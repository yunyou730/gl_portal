#include "DFApplication.h"
#include <cstdio>
#include "DFGLView.h"
#include "DFRenderer.h"
#include "DFMacro.hpp"

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
        _renderer->Clear(_view);
        // @miao @todo
        _renderer->Render();
        
        _view->OnRenderEnd();
        _view->PollEvents();
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
    
}

}
