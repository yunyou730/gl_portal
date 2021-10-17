#include "PerformanceSystem.h"
#include "World.h"
#include "PerformanceSingleton.h"

namespace crude {

PerformanceSystem::PerformanceSystem(World* world)
    :BaseSystem(world)
{
    
}

void PerformanceSystem::Init()
{
    _performance = _world->GetSingleton<PerformanceSingleton>(ESingleton::ST_Performance);
}

void PerformanceSystem::OnUpdate(float deltaTime)
{
    DumpFPS(deltaTime);
    DumpDrawCall();
}

void PerformanceSystem::OnRender()
{
    
}

void PerformanceSystem::Cleanup()
{
    
}

void PerformanceSystem::DumpFPS(float deltaTime)
{
    _elapsedTime += deltaTime;
    
    while(_elapsedTime >= 1.0)
    {
        printf("[fps] %d\n",_fps);
        _elapsedTime -= 1.0;
        _fps = 0;
    }
    _fps++;
}

void PerformanceSystem::DumpDrawCall()
{
    printf("[drawcall] %d\n",_performance->_drawCall);
    _performance->ClearDrawCall();
}

}
