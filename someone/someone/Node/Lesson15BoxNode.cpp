#include "Lesson15BoxNode.h"

void Lesson15BoxNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    GetShader()->SetUniform("u_Tex1",0);
    GetShader()->SetUniform("u_Tex2",1);
}

