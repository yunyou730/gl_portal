#include "TransformComponent.h"

namespace crude
{
TransformComponent::TransformComponent()
{
    
}

void TransformComponent::SetPos(const ayy::Vec3f& pos)
{
    _pos = pos;
}

void TransformComponent::SetRot(const ayy::Vec3f& rot)
{
    _rot = rot;
}

void TransformComponent::SetScale(const ayy::Vec3f& scale)
{
    _scale = scale;
}

}

