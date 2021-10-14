#include "RenderComponent.h"
#include "Ayy.h"
#include "../RenderNode.h"

namespace crude
{

RenderComponent::~RenderComponent()
{
    AYY_SAFE_DEL(_renderNode);
}

void RenderComponent::SetRenderNode(RenderNode* renderNode)
{
    AYY_SAFE_DEL(_renderNode);
    _renderNode = renderNode;
}

void RenderComponent::SetWatchCamera(ayy::Camera* camera)
{
    _watchCamera = camera;
}

}


