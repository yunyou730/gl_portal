#include "PhongTexMatNode.h"
#include "PhongTexMaterial.h"

PhongTexMatNode::PhongTexMatNode()
{
    _material = new PhongTexMaterial();
}

PhongTexMatNode::~PhongTexMatNode()
{
    AYY_SAFE_DEL(_material);
}

void PhongTexMatNode::SetShader(ayy::ShaderProgram* shader)
{
    CommonNode::SetShader(shader);
    _material->SetShader(shader);
}

void PhongTexMatNode::SetMaterial(const ayy::TextureUUID& diffuseTex,const ayy::TextureUUID& specularTex,const float& shininess)
{
    _material->SetDiffuseTexture(diffuseTex);
    _material->SetSpecularTexture(specularTex);
    _material->SetSpecularShininess(shininess);
}

void PhongTexMatNode::SetLight(const ayy::Vec3f& ambient,const ayy::Vec3f& diffuse,const ayy::Vec3f& specular)
{
    _lightAmbient = ambient;
    _lightDiffuse = diffuse;
    _lightSpecular = specular;
}

void PhongTexMatNode::SetViewPos(const ayy::Vec3f& pos)
{
    _viewPos = pos;
}

void PhongTexMatNode::SyncPropToShader(ayy::Camera* mainCam)
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
