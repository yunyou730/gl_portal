#pragma once
#include "BaseSystem.h"


namespace crude {

class PerformanceSingleton;
class PerformanceSystem : public BaseSystem
{
public:
    PerformanceSystem(World* world);
    
    virtual void Init() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender() override;
    virtual void Cleanup() override;
    
protected:
    void DumpFPS(float deltaTime);
    void DumpDrawCall();
    void ShowLog(const std::string& log);
    
protected:
    PerformanceSingleton*   _performance = nullptr;
    
    float _elapsedTime = 0.0f;
    int _fps = 0;
    int _drawCall = 0;
};

}
