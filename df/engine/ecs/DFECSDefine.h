#pragma once

namespace df {
namespace ecs
{

typedef enum
{
    WorldComp_Event,
    WorldComp_Render,
    
    WorldComp_Max,
    
} EWorldCompType;


typedef enum
{
    Sys_None,
    Sys_Event,
    
    
} ESystemType;

}
}
