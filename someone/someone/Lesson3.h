#pragma once
#include "LessonBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ayy
{
class ShaderProgram;
}

class Lesson3 : public LessonBase
{
public:
    Lesson3() {}
    virtual ~Lesson3();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender(float deltaTime) override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO);
    
private:
    GLuint  _vao,_vbo,_ebo;
    ayy::ShaderProgram*  _shader = nullptr;
};
