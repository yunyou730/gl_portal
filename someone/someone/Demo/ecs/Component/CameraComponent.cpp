#include "CameraComponent.h"
#include "Ayy.h"

namespace crude
{

CameraComponent::~CameraComponent()
{

}

void CameraComponent::SetCamera(ayy::Camera* camera)
{
    AYY_SAFE_DEL(_camera);
    _camera = camera;
}

}


