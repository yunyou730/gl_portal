#pragma once

namespace df {

class GLView;
class Renderer;
class Application
{
public:
    Application();
    virtual ~Application();
    
    void Run();
    float GetDeltaTime() const {return _deltaTime;}
    
protected:
    void MainLoop();
    void CalcDeltaTime();
    
protected:
    virtual void DidFinishLaunching();
    virtual void DidEnterBackground();
    virtual void DidEnterForeground();
    virtual void CleanUp();
    
protected:
    GLView*     _view = nullptr;
    Renderer*   _renderer = nullptr;
    float       _deltaTime = 0.f;
};
}
