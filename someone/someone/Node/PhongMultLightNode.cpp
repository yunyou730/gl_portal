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

void PhongMultLightNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    _material->SyncShaderParam();
}
