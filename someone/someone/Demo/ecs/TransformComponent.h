#pragma once

#include "Define.h"
#include "BaseComponent.h"
#include "Ayy.h"

namespace crude {
class TransformComponent : public BaseComponent
{
public:
    TransformComponent();
    
    void SetPos(const ayy::Vec3f& pos);
    void SetRot(const ayy::Vec3f& rot);
    void SetScale(const ayy::Vec3f& scale);
    
    ayy::Vec3f _pos;
    ayy::Vec3f _rot;
    ayy::Vec3f _scale;
};
}

