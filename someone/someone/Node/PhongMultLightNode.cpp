#include "PhongMultLightNode.h"
#include "PhongMultiLightMaterial.h"

PhongMultLightNode::PhongMultLightNode()
{
    _material = new PhongMultiLightMaterial();
}

PhongMultLightNode::~PhongMultLightNode()
{
    AYY_SAFE_DEL(_material);
}

void PhongMultLightNode::SetShader(ayy::ShaderProgram* shader)
{
    CommonNode::SetShader(shader);
    _material->SetShader(shader);
}


void PhongMultLightNode::SetViewPos(const ayy::Vec3f& pos)
{
    _viewPos = pos;
}

void PhongMultLightNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    /*
    _shader->SetUniform("u_Light.ambient",_lightAmbient);
    _shader->SetUniform("u_Light.diffuse",_lightDiffuse);
    _shader->SetUniform("u_Light.specular",_lightSpecular);
    glCheckError();
    _shader->SetUniform("u_Light.position",_lightSourcePos);
    glCheckError();
    _shader->SetUniform("u_ViewPos",_viewPos);
    glCheckError();
    */
    
    // set material params
    _material->SyncShaderParam();
}
