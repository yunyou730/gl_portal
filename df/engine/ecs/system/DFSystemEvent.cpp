#include "DFSystemEvent.h"
#include "DFWorld.h"
#include "DFEventComp.h"

namespace df {
namespace ecs{

using ListenFunc = std::function<void(df::EventBase* evt)>;


SystemEvent::SystemEvent()
    :SystemBase(ESystemType::Sys_Event)
{
    
}

SystemEvent::~SystemEvent()
{
    
}

void SystemEvent::Tick(WorldBase* world,float deltaTime)
{
//    SystemBase::Tick(world,deltaTime);
    
    World* w = dynamic_cast<World*>(world);
    EventComp* evtComp = w->GetEvtSingleton();
    
    for(auto it : evtComp->_evtArray)
    {
        df::EventBase* evt = it;
        
        auto it2 = evtComp->_listenerMap.find(evt->evtType);
        if(it2 != evtComp->_listenerMap.end())
        {
            std::vector<Listener>& listenerList = it2->second;
            
            for(int i = 0;i < listenerList.size();i++)
            {
                Listener& l = listenerList[i];
                l.func(evt);
            }
        }
    }
    
    evtComp->Clear();
    
}

}
}
