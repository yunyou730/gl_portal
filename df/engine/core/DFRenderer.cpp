#include "DFRenderer.h"
#include "DFGLView.h"

namespace df {

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    
}

void Renderer::Clear(GLView* view)
{
    glViewport(0,0,view->Width(),view->Height());
    glClearColor(_clearColor.r,_clearColor.g,_clearColor.b,_clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render()
{
    for(auto it : _commandList)
    {
        RenderWithCommand(it);
    }
}

void Renderer::EndRender()
{
    _commandList.clear();
}

void Renderer::AddRenderCommand(RenderCommand* command)
{
    _commandList.push_back(command);
}

void Renderer::RenderWithCommand(RenderCommand* command)
{
//    switch(RenderCommand)
//    {
//
//
//    }
}

}

