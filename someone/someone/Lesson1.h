#pragma once
#include "BaseScene.h"

namespace ayy
{
class ShaderProgram;
}

class Lesson1 : public ayy::BaseScene
{
public:
    ~Lesson1();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO);
    
private:
    GLuint  _vao,_vbo;
    ayy::ShaderProgram*  _shader = nullptr;
};
