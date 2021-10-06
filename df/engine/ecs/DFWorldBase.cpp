#include "DFWorldBase.h"

#include "system/DFSystemEvent.h"

namespace df {
namespace ecs {

WorldBase::WorldBase()
{
    
}

WorldBase::~WorldBase()
{
    CleanUp();
}

void WorldBase::Init()
{
    InitSystems();
    InitWorldComps();
}

void WorldBase::CleanUp()
{
    for(auto it = _systemMap.begin();it != _systemMap.end();it++)
    {
        delete it->second;
    }
    _systemMap.clear();
}

void WorldBase::OnTick(float deltaTime)
{
    for(auto sys : _systemMap)
    {
        sys.second->Tick(this,deltaTime);
    }
}

}
}
