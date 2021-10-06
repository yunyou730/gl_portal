#pragma once

namespace df {

class GLView;
class Renderer;

namespace ecs {
    class World;
}

class Application
{
public:
    Application();
    virtual ~Application();
    
    static Application* GetInstance() { return s_instance;}
    
    void Run();
    float GetDeltaTime() const {return _deltaTime;}
    
    void SetDesireFPS(int desireFPS) { _desireFPS = desireFPS;}
    
    df::ecs::World* GetWorld() { return _world;}
    
protected:
    void MainLoop();
    void CalcDeltaTime();
    float GetDesireDeltaTime() const;
    
protected:
    virtual void DidFinishLaunching();
    virtual void DidEnterBackground();
    virtual void DidEnterForeground();
    virtual void CleanUp();
    
protected:
    GLView*     _view = nullptr;
    Renderer*   _renderer = nullptr;
    float       _deltaTime = 0.f;
    
    int         _desireFPS = 30;
    
    df::ecs::World* _world = nullptr;
    
    
    static Application* s_instance;
};
}
