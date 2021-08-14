#include "SkyBoxNode.h"

void SkyBoxNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    ayy::TextureManager::GetInstance()->BindTextureToCube(_texUUID);
    glDepthMask(GL_FALSE);
}

void SkyBoxNode::AfterDraw()
{
    glDepthMask(GL_TRUE);
    ayy::TextureManager::GetInstance()->UnBindCubeTexture(_texUUID);
}
