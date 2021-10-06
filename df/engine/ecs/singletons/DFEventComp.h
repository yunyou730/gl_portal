#pragma once
#include "DFWorldComp.h"
#include "../../core/DFEvent.h"
#include <map>
#include <vector>

namespace df {
namespace ecs {

using ListenFunc = std::function<void(df::EventBase* evt)>;

struct Listener
{
    int listenerId = 0;
    ListenFunc func = nullptr;
};

class EventComp : public WorldComp
{
public:
    void AddEvent(df::EventBase* evt);
    int AddListener(EEventType evtType,std::function<void(df::EventBase* evt)>);
    void RemoveListener(EEventType evtType,int listenerHandle);
    void Clear();
    
    std::vector<df::EventBase*> _evtArray;
    std::map<EEventType,std::vector<Listener>> _listenerMap;
protected:
    
    int _listenerHandleCount = 0;
};
}
}
