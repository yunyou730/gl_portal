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
    virtual void OnViewportSizeChanged(int width,int height) override;
    
protected:
    void PrepareGroundMesh();
    void PrepareBoxMesh();
    void PrepareShadowMap();
    
    void DrawScene();
    void DrawShadowMap();
    void DrawGround(ayy::ShaderProgram* shader,ayy::Camera* camera,ayy::Camera* light);
    void DrawBoxes(ayy::ShaderProgram* shader,ayy::Camera* camera,ayy::Camera* light);    
    void DrawDepthBufferImg();
    
protected:
    GLuint  _groundVAO,_groundVBO,_groundEBO;
    GLuint  _boxVAO,_boxVBO,_boxEBO;
    
    ayy::ShaderProgram* _groundShader   = nullptr;
    ayy::ShaderProgram* _boxShader      = nullptr;
    ayy::ShaderProgram* _depthMapShader = nullptr;
    
    crude::FreeCamera*  _camera         = nullptr;
    ayy::Camera*        _light          = nullptr;
    
    GLuint  _depthFBO;
    GLuint  _depthMap;
    
    const GLuint kShadowWidth;
    const GLuint kShadowHeight;

    
    crude::TransformComponent _groundTransform;
    std::vector<crude::TransformComponent> _boxes;
};
