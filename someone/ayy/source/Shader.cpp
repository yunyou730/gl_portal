#include "../headers/Shader.h"
#include <cassert>

namespace ayy {

ShaderProgram* ShaderProgram::CreateShaderProgram(const std::string& vsSource,const std::string& fsSource)
{
    const char* vsSourceAlias = vsSource.c_str();
    const char* fsSourceAlias = fsSource.c_str();
    
    ShaderProgram* shader = new ShaderProgram();
    int success = 0;
    
    // vs
    shader->vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vs,1,&vsSourceAlias,nullptr);
    glCompileShader(shader->vs);
    
    char infoLog[512];
    glGetShaderiv(shader->vs,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader->vs,512,nullptr,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
    }
    
    // fs
    shader->fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fs,1,&fsSourceAlias,nullptr);
    glCompileShader(shader->fs);
    glGetShaderiv(shader->fs,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader->fs,512,nullptr,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
    }
    
    // program
    shader->program = glCreateProgram();
    glAttachShader(shader->program,shader->vs);
    glAttachShader(shader->program,shader->fs);
    glLinkProgram(shader->program);
    glGetProgramiv(shader->program,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(shader->program,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(shader->vs);
    glDeleteShader(shader->fs);
    
    shader->vs = 0;
    shader->fs = 0;
    
    return shader;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program);
    program = 0;
}

void ShaderProgram::Use()
{
    glUseProgram(program);
}

void ShaderProgram::UnUse()
{
    glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& uniformName,const ayy::Vec4f& value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform4f(location,value.x,value.y,value.z,value.w);
}

void ShaderProgram::SetUniform(const std::string& uniformName,float value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform1f(location,value);
}

void ShaderProgram::SetUniform(const std::string& uniformName,int value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform1i(location,value);
}

}


