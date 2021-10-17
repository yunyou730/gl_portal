#pragma once
#include "Ayy.h"
#include <vector>
#include "../Demo/ecs/Component/TransformComponent.h"

/*
 Learn OpenGL
 Shadow Map
 **/

namespace crude
{
class FreeCamera;
}

class Crude3 : public ayy::BaseScene
{
public:
    Crude3(int viewportWidth,int viewportHeight);
    ~Crude3();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareGroundMesh();
    void PrepareBoxMesh();
    
    void DrawGround();
    void DrawBoxes();
    
protected:
    GLuint  _groundVAO,_groundVBO,_groundEBO;
    GLuint  _boxVAO,_boxVBO,_boxEBO;
    
    ayy::ShaderProgram* _groundShader   = nullptr;
    ayy::ShaderProgram* _boxShader      = nullptr;
    
    crude::FreeCamera*        _camera = nullptr;
    
    crude::TransformComponent _groundTransform;    
    std::vector<crude::TransformComponent> _boxes;
};
