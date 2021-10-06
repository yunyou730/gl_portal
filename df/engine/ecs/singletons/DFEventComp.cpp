#include "DFEventComp.h"

namespace df {
namespace ecs {

void EventComp::AddEvent(df::EventBase* evt)
{
    _evtArray.push_back(evt);
}

int EventComp::AddListener(EEventType evtType,ListenFunc func)
{
    auto it = _listenerMap.find(evtType);
    
    std::vector<Listener>* arr = nullptr;
    if(it == _listenerMap.end())
    {
        _listenerMap.insert(std::make_pair(evtType,std::vector<Listener>()));
    }
    arr = &_listenerMap[evtType];
    
    
    Listener l;
    l.func = func;
    l.listenerId = ++_listenerHandleCount;
    
    arr->push_back(l);
    
    return ++_listenerHandleCount;
}

void EventComp::RemoveListener(EEventType evtType,int listenerHandle)
{
    auto it = _listenerMap.find(evtType);
    if(it == _listenerMap.end())
    {
        return;
    }
    
    std::vector<Listener>& arr = it->second;
    for(auto it2 = arr.begin();it2 != arr.end();)
    {
        if(it2->listenerId == listenerHandle)
        {
            it2 = arr.erase(it2);
        }
        else
        {
            it2++;
        }
    }
}

void EventComp::Clear()
{
    for(auto it:_evtArray)
    {
        delete it;
    }
    _evtArray.clear();
}

}
}
