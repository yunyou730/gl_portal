#include "TransformComponent.h"

namespace crude
{
TransformComponent::TransformComponent()
{
    _scale = ayy::Vec3f(1.0,1.0,1.0);
    _rot = ayy::Vec3f(0.0,0.0,0.0);
    _pos = ayy::Vec3f(0.0,0.0,0.0);
}

void TransformComponent::SetPos(const ayy::Vec3f& pos)
{
    _pos = pos;
    _bDirty = true;
}

void TransformComponent::SetRot(const ayy::Vec3f& rot)
{
    _rot = rot;
    _bDirty = true;
}

void TransformComponent::SetScale(const ayy::Vec3f& scale)
{
    _scale = scale;
    _bDirty = true;
}

ayy::Mat4x4f* TransformComponent::GetWorldMatrix()
{
    if(_bDirty)
    {
        CalcWorldMatrix();
        _bDirty = false;
    }
    return &_worldMatrix;
}

void TransformComponent::CalcWorldMatrix()
{
    ayy::Mat4x4f matScale,matRotX,matRotY,matRotZ,matTranslate;
    
    ayy::MakeScaleMatrix(matScale, _scale.x(),_scale.y(),_scale.z());

    ayy::MakeRotateByXMatrix(matRotX,_rot.x());
    ayy::MakeRotateByXMatrix(matRotY,_rot.y());
    ayy::MakeRotateByXMatrix(matRotZ,_rot.z());
    
    ayy::MakeTranslateMatrix(matTranslate,_pos.x(),_pos.y(),_pos.z());
    
    _worldMatrix = matScale * matRotX * matRotY * matRotZ * matTranslate;
}

}

