#pragma once
#include "LessonBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ayy
{
class ShaderProgram;
}

class Lesson5 : public LessonBase
{
public:
    ~Lesson5();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO);
    void PrepareTexture(GLuint& tid);
    
private:
    GLuint  _vao,_vbo,_ebo;
    ayy::ShaderProgram*  _shader = nullptr;
    
    GLuint  _tID;
};
