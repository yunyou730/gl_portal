#pragma once

#include "DFWorldBase.h"
#include "../core/DFEvent.h"
#include <functional>

namespace df {
namespace ecs {


class EventComp;
class World : public WorldBase
{
public:
    virtual void InitSystems() override;
    virtual void InitWorldComps() override;
    
    df::ecs::WorldComp* GetSingleton(df::ecs::EWorldCompType compType);
    df::ecs::EventComp* GetEvtSingleton();
    
public:
    void DispatchEvent(EventBase* evtInfo);
    int RegisterEvent(EEventType evtType,std::function<void(df::EventBase*)>);
    void UnRegisterEvent(EEventType evtType,int listenerHandle);
};
}
}
