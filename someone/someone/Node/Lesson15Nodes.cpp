#include "Lesson15Nodes.h"

void Lesson15BoxNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    GetShader()->SetUniform("u_Tex1",0);
//    GetShader()->SetUniform("u_Tex2",1);
}

void Lesson15PlaneNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    GetShader()->SetUniform("u_Tex1",0);
}

void Lesson15BorderNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
}

