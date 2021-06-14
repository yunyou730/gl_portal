#pragma once
#include "LessonBase.h"

namespace ayy
{
class ShaderProgram;
}

class Lesson1 : public LessonBase
{
public:
    ~Lesson1();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnUpdate(float deltaTime) override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO);
    
private:
    GLuint  _vao,_vbo;
    ayy::ShaderProgram*  _shader = nullptr;
};
