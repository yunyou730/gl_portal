#include "SkyBoxNode.h"

void SkyBoxNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
//    GetShader()->SetUniform("u_Tex1",0);
//    GetShader()->SetUniform("u_Tex2",1);
    ayy::TextureManager::GetInstance()->BindTextureToCube(_texUUID);
    glDepthMask(GL_FALSE);
}

void SkyBoxNode::AfterDraw()
{
    glDepthMask(GL_TRUE);
}
