#pragma once
#include "Ayy.h"
#include "RenderNode.h"

namespace crude {

class BlockRender : public RenderNode
{
public:
    BlockRender();
    virtual ~BlockRender();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix) override;
    
protected:
    void PrepareMesh();
    
protected:
    GLuint _vao,_vbo,_ebo;
    ayy::ShaderProgram* _shader = nullptr;
};

}

