#pragma once
#include "LessonBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ayy
{
class ShaderProgram;
}

class Lesson4 : public LessonBase
{
public:
    ~Lesson4();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnUpdate(float deltaTime) override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO);
    
private:
    GLuint  _vao,_vbo,_ebo;
    ayy::ShaderProgram*  _shader = nullptr;
};
