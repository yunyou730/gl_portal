#pragma once
#include "Ayy.h"
#include "Define.h"
#include "SingletonComponent.h"
#include <vector>

namespace crude {
class CameraSingleton : public SingletonComponent
{
public:
    virtual ~CameraSingleton();
    
    void RegisterCamera(ayy::Camera* camera);
    ayy::Camera* GetMainCamera() { return _mainCamera;}
    
    ayy::Camera*    _mainCamera = nullptr;
    
};

}

