#include "RenderNode.h"

namespace crude
{
void RenderNode::ApplyRenderState()
{
    glDepthMask(_renderState.bEnableDepthWrite);
}

}



