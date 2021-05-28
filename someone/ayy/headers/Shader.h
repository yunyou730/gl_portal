#pragma once
#include <glad/glad.h>
#include <iostream>
#include "Math.h"

namespace ayy {

class ShaderProgram
{
public:
    static ShaderProgram* CreateShaderProgram(const std::string& vsSource,const std::string& fsSource);
    ~ShaderProgram();
    
    void Use();
    void UnUse();
    
    void SetUniform(const std::string& uniformName,const ayy::Vec4f& value);
    void SetUniform(const std::string& uniformName,float value);
    
public:
    GLuint program = 0;
    GLuint vs = 0;
    GLuint fs = 0;
};

}

