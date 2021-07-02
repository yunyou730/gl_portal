#include "PhongMatNode.h"
#include "PhongMaterial.h"

PhongMatNode::PhongMatNode()
{
    _material = new PhongMaterial();
}

PhongMatNode::~PhongMatNode()
{
    AYY_SAFE_DEL(_material);
}

void PhongMatNode::SetShader(ayy::ShaderProgram* shader)
{
    CommonNode::SetShader(shader);
    _material->SetShader(shader);
}

void PhongMatNode::SetMaterial(const ayy::Vec3f& ambient,const ayy::Vec3f& diffuse,const ayy::Vec3f& specular,float shininess)
{
    _material->SetAmbientColor(ambient);
    _material->SetDiffuseColor(diffuse);
    _material->SetSpecularColor(specular);
    _material->SetSpecularShininess(shininess);
}

void PhongMatNode::SetLight(const ayy::Vec3f& ambient,const ayy::Vec3f& diffuse,const ayy::Vec3f& specular)
{
    _lightAmbient = ambient;
    _lightDiffuse = diffuse;
    _lightSpecular = specular;
}

void PhongMatNode::SetViewPos(const ayy::Vec3f& pos)
{
    _viewPos = pos;
}

void PhongMatNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    
    _shader->SetUniform("u_Light.ambient",_lightAmbient);
    _shader->SetUniform("u_Light.diffuse",_lightDiffuse);
    _shader->SetUniform("u_Light.specular",_lightSpecular);
    glCheckError();
    _shader->SetUniform("u_Light.position",_lightSourcePos);
    glCheckError();
    _shader->SetUniform("u_ViewPos",_viewPos);
    glCheckError();
    
    // set material params
    _material->SyncShaderParam();
}
