#pragma once
#include "Ayy.h"

namespace crude {

struct RenderState
{
    bool bEnableDepthWrite = true;
    
    // alpha blend
    // depth test
    // ...
};

class RenderNode
{
public:
    virtual ~RenderNode() {}
    
    virtual void Initiate() = 0;
    virtual void CleanUp() = 0;
    
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix) = 0;
    
    void ApplyRenderState();
    
protected:
    RenderState     _renderState;
};

}

