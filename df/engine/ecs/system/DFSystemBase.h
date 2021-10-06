#pragma once
#include "DFECSDefine.h"

namespace df {
namespace ecs {

class WorldBase;
class SystemBase
{
public:
    SystemBase(ESystemType sysType);
    virtual ~SystemBase();
    
    virtual void Tick(WorldBase* world,float deltaTime) = 0;
};

}
}
