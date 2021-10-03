#pragma once

#include "../base/DFColor.h"
#include <vector>

namespace df {
class GLView;
class RenderCommand;
class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    void SetClearColor(const Color4F& color) {_clearColor = color;}
    
    void Clear(GLView* view);
    
    // foreach commands
    void Render();
    
    void AddRenderCommand(RenderCommand* command);
    
protected:
    void EndRender();
    void RenderWithCommand(RenderCommand* command);
    
protected:
    Color4F _clearColor;
    std::vector<RenderCommand*> _commandList;
};
}
