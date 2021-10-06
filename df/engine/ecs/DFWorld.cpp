#include "DFWorld.h"
#include <map>
#include <cassert>

#include "system/DFSystemEvent.h"
#include "singletons/DFEventComp.h"
#include "singletons/DFWorldComp.h"

namespace df {
namespace ecs {

void World::InitSystems()
{
    _systemMap.insert(std::make_pair(ESystemType::Sys_Event,new SystemEvent()));
}

void World::InitWorldComps()
{
    _worldCompMap.insert(std::make_pair(EWorldCompType::WorldComp_Event,new EventComp()));
}


df::ecs::WorldComp* World::GetSingleton(df::ecs::EWorldCompType compType)
{
    auto it = _worldCompMap.find(EWorldCompType::WorldComp_Event);
    if(it == _worldCompMap.end())
        return nullptr;
    return it->second;
}

df::ecs::EventComp* World::GetEvtSingleton()
{
    df::ecs::WorldComp* comp = GetSingleton(EWorldCompType::WorldComp_Event);
    return dynamic_cast<df::ecs::EventComp*>(comp);
}

void World::DispatchEvent(EventBase* evtInfo)
{
    GetEvtSingleton()->AddEvent(evtInfo);
}

int World::RegisterEvent(EEventType evtType,std::function<void(df::EventBase*)> func)
{
    return GetEvtSingleton()->AddListener(evtType,func);
}

void World::UnRegisterEvent(EEventType evtType,int listenerHandle)
{
    GetEvtSingleton()->RemoveListener(evtType,listenerHandle);
}


}
}
