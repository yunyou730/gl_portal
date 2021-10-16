#pragma once
#include "Ayy.h"
#include "RenderNode.h"

namespace crude {

struct GroundRenderParam
{
    int rows = 1;
    int cols = 1;
};

class Ground : public RenderNode
{
public:
    Ground();
    virtual ~Ground();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix) override;
    
    ayy::ShaderProgram* GetShader() { return _shader;}
    GroundRenderParam* GetRenderParam() { return &_renderParam;}
    
protected:
    void PrepareMesh();
    
protected:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    ayy::ShaderProgram* _shader = nullptr;
    
    GroundRenderParam   _renderParam;
};

}
