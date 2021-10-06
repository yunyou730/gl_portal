#pragma once
#include <map>
#include "DFECSDefine.h"

namespace df {
namespace ecs {

class WorldComp;
class SystemBase;
class SystemEvent;
class WorldBase
{
public:
    WorldBase();
    virtual ~WorldBase();
    
    virtual void Init();
    virtual void CleanUp();
    virtual void OnTick(float deltaTime);
    
protected:
    virtual void InitSystems() = 0;
    virtual void InitWorldComps() = 0;
    
protected:
    std::map<ESystemType,SystemBase*>    _systemMap;
    std::map<EWorldCompType,WorldComp*> _worldCompMap;
    
};
}
}
