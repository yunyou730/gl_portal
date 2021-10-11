#pragma once
#include "Ayy.h"
#include "Entity.h"

namespace crude {

class Ground : public Entity
{
public:
    Ground();
    virtual ~Ground();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera) override;
    
protected:
    void PrepareMesh();
    
protected:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    ayy::ShaderProgram* _shader = nullptr;
};

}
