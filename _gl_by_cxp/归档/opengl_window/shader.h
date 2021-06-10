//
//  shader.h
//  opengl_window
//
//  Created by Tina Green on 2019/8/27.
//  Copyright © 2019 Tina Green. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include <glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"imgui/imgui.h"

class Shader {
public:
    unsigned int id;
    Shader(const GLchar* vertexpath, const GLchar* fragmentpath);
    void use();
    void set4float(const std::string &name, float value1,float value2, float value3, float value4) const;
    void set1float(const std::string &name, float value) const;
    void setbool(const std::string &name, bool value) const;
    void setint(const std::string &name, int value) const;
    void setmat(const std::string &name, glm::mat4 trans) const;
    void set3float(const std::string &name, float value1,float value2, float value3) const;
    void setvec3(const std::string &name,glm::vec3 value) const;
    void setvec2(const std::string &name,glm::vec2 value) const;
    void setvec3(const std::string &name,ImVec4 value) const;
};

Shader::Shader(const GLchar* vertexpath, const GLchar* fragmentpath)
{
    std::string vertexcode;
    std::string fragmentcode;//创建符串类
    std::ifstream vshaderfile;//创建输入文件流
    std::ifstream fshaderfile;
    
    vshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vshaderfile.open(vertexpath);
        fshaderfile.open(fragmentpath);
        std::stringstream vshaderstream, fshaderstream;
        vshaderstream<< vshaderfile.rdbuf();
        fshaderstream<< fshaderfile.rdbuf();
        vshaderfile.close();
        fshaderfile.close();
        vertexcode=vshaderstream.str();
        fragmentcode=fshaderstream.str();
    }
    catch(std::ifstream::failure e){
        std::cout<<"error shaderfile not successfully read"<<std::endl;
    }
    const char* vshadercode=vertexcode.c_str();
    const char* fshadercode=fragmentcode.c_str();
    
    unsigned int vertex,fragment;
    
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vshadercode,NULL);
    glCompileShader(vertex);
    
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fshadercode,NULL);
    glCompileShader(fragment);
    
    id=glCreateProgram();
    glAttachShader(id,vertex);
    glAttachShader(id,fragment);
    glLinkProgram(id);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
}

void Shader::use(){
    glUseProgram(id);
}

void Shader::setbool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id,name.c_str()),(int) value);
}

void Shader::setint(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::set4float(const std::string &name, float value1,float value2, float value3, float value4) const{
    glUniform4f(glGetUniformLocation(id,name.c_str()), value1,value2,value3,value4);
}
void Shader::set1float(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(id,name.c_str()), value);
}
void Shader::setmat(const std::string &name, glm::mat4 trans) const{
    glUniformMatrix4fv(glGetUniformLocation(id,name.c_str()),1,GL_FALSE,glm::value_ptr(trans));
}
void Shader::set3float(const std::string &name, float value1,float value2, float value3) const{
    glUniform3f(glGetUniformLocation(id,name.c_str()), value1,value2,value3);
}
void Shader::setvec3(const std::string &name,glm::vec3 value) const{
    glUniform3f(glGetUniformLocation(id,name.c_str()), value.x,value.y,value.z);
}
void Shader::setvec2(const std::string &name,glm::vec2 value) const{
    glUniform2f(glGetUniformLocation(id,name.c_str()), value.x,value.y);
}
void Shader::setvec3(const std::string &name,ImVec4 value) const{
    glUniform3f(glGetUniformLocation(id,name.c_str()), value.x,value.y,value.z);
}

#endif /* shader_h */
