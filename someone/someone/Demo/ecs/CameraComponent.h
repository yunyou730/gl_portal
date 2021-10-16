#pragma once

#include "Define.h"
#include "BaseComponent.h"

namespace ayy {
    class Camera;
}
namespace crude {
class CameraComponent : public BaseComponent
{
public:
    virtual ~CameraComponent();
    void SetCamera(ayy::Camera* camera);
    
    ayy::Camera* _camera = nullptr;
};
}

