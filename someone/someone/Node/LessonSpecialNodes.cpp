#include "LessonSpecialNodes.h"

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

void Lesson15WindowNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    GetShader()->SetUniform("u_Tex1",0);
}

void Lesson16PostProcessNode::SyncPropToShader(ayy::Camera* mainCam)
{
    // do not call CommonNode::SyncPropToShader(mainCam);
    // cause we don't have model ,view ,projection matrics
    GetShader()->SetUniform("u_PostProcessIndex",postProcessIndex);
    GetShader()->SetUniform("u_FramebufferTexture",0);
}

void Lessin18ReflectNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    
    ayy::Vec3f camPos = mainCam->GetPos();
    GetShader()->SetUniform("u_CameraPos",camPos);
}

Lesson19ModelNode::Lesson19ModelNode(const std::string& modelPath,const std::string& prefixPath)
{
    _model = new ayy::model::Model();
    _model->Load(modelPath, prefixPath);
}

Lesson19ModelNode::~Lesson19ModelNode()
{
    AYY_SAFE_DEL(_model);
}

void Lesson19ModelNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    ayy::Vec3f camPos = mainCam->GetPos();
    GetShader()->SetUniform("u_CameraPos",camPos);
}

void Lesson19ModelNode::OnRender(ayy::Camera* mainCam)
{
    CommonNode::OnRender(mainCam);
    _model->DoDraw();
}
