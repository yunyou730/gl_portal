#pragma once

namespace crude {

typedef unsigned int EntityID;

typedef enum
{
    Render,
    Transform,
    Camera,
    KeyboardInput,
    
} ECompType;

typedef enum
{
    ST_Map,
    ST_Spawn,
    ST_Camera,
    
} ESingleton;

typedef enum
{
    Road,
    Block,
    
} ETileType;


typedef enum
{
    AT_Block,
    
    AT_None,
    
} EActorType;

}

