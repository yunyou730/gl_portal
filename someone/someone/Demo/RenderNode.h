#pragma once
#include "Ayy.h"

namespace crude {

class RenderNode
{
public:
    virtual ~RenderNode() {}
    
    virtual void Initiate() = 0;
    virtual void CleanUp() = 0;
    
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnDraw(ayy::Camera* camera) = 0;
};

}

