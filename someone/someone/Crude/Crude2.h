#pragma once
#include "Ayy.h"
#include <vector>

namespace crude
{
class FreeCamera;
class Ground;
class Wall;
class MapRecord;


class World;
}

class Crude2 : public ayy::BaseScene
{
public:
    Crude2(int viewportWidth,int viewportHeight);
    ~Crude2();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareMesh();
    
protected:
    GLuint  _vao = 0;
    GLuint  _vbo = 0;
    GLuint  _vboOffset = 0;
    ayy::ShaderProgram* _shader = nullptr;
    
    crude::FreeCamera*      _camera = nullptr;
    
    
    crude::World*           _world = nullptr;
};
