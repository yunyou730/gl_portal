#pragma once
#include <glad/glad.h>
#include <iostream>
#include "AYYMath.h"

namespace ayy {

class ShaderProgram
{
public:
    static ShaderProgram* CreateShaderProgram(const std::string& vsSource,const std::string& fsSource);
    ~ShaderProgram();
    
    void Use();
    void UnUse();
    
    void SetUniform(const std::string& uniformName,const ayy::Vec4f& value);
    void SetUniform(const std::string& uniformName,const ayy::Vec3f& value);
    void SetUniform(const std::string& uniformName,const ayy::Vec2f& value);
    void SetUniform(const std::string& uniformName,float value);
    void SetUniform(const std::string& uniformName,int value);
    void SetUniform(const std::string& uniformName,bool bValue);
    void SetUniformMat4x4(const std::string& uniformName,float* data);
    
public:
    GLuint program = 0;
    GLuint vs = 0;
    GLuint fs = 0;
};

}

