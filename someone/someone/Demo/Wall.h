#pragma once
#include "Ayy.h"
#include "RenderNode.h"

namespace crude {

class Wall : public RenderNode
{
public:
    Wall();
    virtual ~Wall();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera) override;
    
protected:
    void PrepareMesh();
    
protected:
    GLuint _vao,_vbo,_ebo;
    ayy::ShaderProgram* _shader = nullptr;
};

}

