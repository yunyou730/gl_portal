#pragma once
#include <glad/glad.h>
#include <iostream>

namespace ayy {

class ShaderProgram
{
public:
    static ShaderProgram* CreateShaderProgram(const std::string& vsSource,const std::string& fsSource);
    ~ShaderProgram();
    
public:
    GLuint program = 0;
    GLuint vs = 0;
    GLuint fs = 0;
};

}

