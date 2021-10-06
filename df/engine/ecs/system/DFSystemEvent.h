#pragma once
#include "DFSystemBase.h"

namespace df {
namespace ecs{

class WorldBase;
class SystemEvent : public SystemBase
{
public:
    SystemEvent();
    virtual ~SystemEvent();
    
    
    virtual void Tick(WorldBase* world,float deltaTime) override;
    
};

    
}
}
