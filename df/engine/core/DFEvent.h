#pragma once

namespace df {
namespace ecs
{
class World;
}
}

namespace df {
    
typedef enum
{
    EKeyPress,
    
    
} EEventType;


struct EventBase
{
public:
    EventBase(EEventType evtType):evtType(evtType){}
    EEventType evtType;
};

struct EventKeyPress : public EventBase
{
public:
    EventKeyPress(int keyCode)
        :EventBase(EEventType::EKeyPress)
        ,keyCode(keyCode)
    {
        
    }
    int keyCode;
};

}
