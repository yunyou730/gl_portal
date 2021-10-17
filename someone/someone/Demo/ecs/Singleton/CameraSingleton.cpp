#include "CameraSingleton.h"

namespace crude
{

CameraSingleton::~CameraSingleton()
{

}

void CameraSingleton::RegisterCamera(ayy::Camera* camera)
{
    _mainCamera = camera;
}

}
