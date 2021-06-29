#include "PhongNode.h"

void PhongNode::SetLightSourcePos(const ayy::Vec3f& lightSourcePos)
{
    _lightSourcePos = lightSourcePos;
}

void PhongNode::SetLightColor(const ayy::Vec3f& color)
{

    _lightColor = color;
}

void PhongNode::SetObjectColor(const ayy::Vec3f& color)
{
    _objectColor = color;
}


void PhongNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    
    _shader->SetUniform("u_LightColor",_lightColor);
    glCheckError();
    _shader->SetUniform("u_ObjColor",_objectColor);
    glCheckError();
}
