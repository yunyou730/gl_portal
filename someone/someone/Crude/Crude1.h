#pragma once
#include "Ayy.h"
#include <vector>

/*
 Learn OpenGL Instance rendering
 **/
class Crude1 : public ayy::BaseScene
{
public:
    Crude1(int viewportWidth,int viewportHeight);
    ~Crude1();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    
protected:
    GLuint  _vao = 0;
    GLuint  _vbo = 0;
    GLuint  _vboOffset = 0;
    ayy::ShaderProgram* _shader = nullptr;
//    std::vector<ayy::Vec2f> _offsets;
};
