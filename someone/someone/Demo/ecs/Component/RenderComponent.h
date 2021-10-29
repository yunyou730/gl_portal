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
    RenderNode* _renderNode = nullptr;
public:
    // todo
    // 记录渲染状态
    // MSAA 混合模式 depth stencil test ...
    // 是否开启 CullFace  , Cull 哪个 Front or Back
};
}
