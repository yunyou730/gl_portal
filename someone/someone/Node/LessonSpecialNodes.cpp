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

/// Lesson20NormalMapNode
void Lesson20NormalMapNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    
    // normal map
    GetShader()->SetUniform("u_EnableNormalMap",_bEnableNormalmap);
    GetShader()->SetUniform("u_EnableWrongNormalMap",_bEnableWrongNormalMap);
    
    // common
    GetShader()->SetUniform("u_NormalMap",1);
    GetShader()->SetUniform("u_CameraPos",mainCam->GetPos());
    
    // point light
    GetShader()->SetUniform("u_PointLight.position",_pointLightPos);
    GetShader()->SetUniform("u_PointLight.ambient",_pointLightAmbient);
    GetShader()->SetUniform("u_PointLight.diffuse",_pointLightDiffuse);
    GetShader()->SetUniform("u_PointLight.specular",_pointLightSpecular);
    GetShader()->SetUniform("u_PointLight.constant",_pointLightConstant);
    GetShader()->SetUniform("u_PointLight.linear",_pointLightLinear);
    GetShader()->SetUniform("u_PointLight.quadratic",_pointLightQuadratic);
    
//    GetShader()->SetUniform("u_SpotLight.ambient",ayy::Vec3f(1.0,1.0,1.0));
//    GetShader()->SetUniform("u_SpotLight.ambient",ayy::Vec3f(0.0,0.0,0.0));
//    GetShader()->SetUniform("u_SpotLight.diffuse",ayy::Vec3f(1.0,1.0,1.0));
//    GetShader()->SetUniform("u_SpotLight.specular",ayy::Vec3f(1.0,1.0,1.0));
    
    // material
    GetShader()->SetUniform("u_Material.diffuse",0);
    GetShader()->SetUniform("u_Material.shininess",32.0f);
}

void Lesson21TestSDF::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    GetShader()->SetUniform("u_Glyph",0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
