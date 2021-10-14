#pragma once

#include "Define.h"
#include "BaseComponent.h"

namespace ayy {
    class Camera;
}
namespace crude {
class RenderNode;
class RenderComponent : public BaseComponent
{
public:
    virtual ~RenderComponent();
    void SetRenderNode(RenderNode* renderNode);
    void SetWatchCamera(ayy::Camera* camera);
    
    ayy::Camera* _watchCamera = nullptr;
    RenderNode* _renderNode = nullptr;
};
}

