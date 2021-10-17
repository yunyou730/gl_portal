#pragma once
#include "Ayy.h"
#include "Define.h"
#include "SingletonComponent.h"
#include <vector>

namespace crude {

class PerformanceSingleton : public SingletonComponent
{
public:
    void AddDrawCall(){ _drawCall++;}
    void ClearDrawCall() {_drawCall = 0;}
public:
    int _drawCall;
};

}

