#pragma once
#include "LessonBase.h"
#include <glad/glad.h>

namespace ayy
{
class ShaderProgram;
}

class Lesson2 : public LessonBase
{
public:
    ~Lesson2();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender(float deltaTime) override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO);
    
private:
    GLuint  _vao,_vbo,_ebo;
    ayy::ShaderProgram*  _shader = nullptr;
};
