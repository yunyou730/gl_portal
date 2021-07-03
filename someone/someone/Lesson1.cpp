#include "Lesson1.h"
#include "../ayy/headers/Shader.h"

static const char* vsSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(vec3(aPos), 1.0);
}
)";

static const char* fsSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0,0.5,0.2,1.0);
}
)";

Lesson1::~Lesson1()
{
    
}

void Lesson1::Prepare()
{
    _shader = ayy::ShaderProgram::CreateShaderProgram(vsSource, fsSource);
    PrepareMesh(_vao,_vbo);
}

void Lesson1::Cleanup()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    delete _shader;
}

void Lesson1::OnRender()
{
    // Do Render
    glUseProgram(_shader->program);
    glBindVertexArray(_vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES,0,3);
}

// set up vertex data (and buffer(s)) and configure vertex attributes
void Lesson1::PrepareMesh(GLuint& VAO,GLuint& VBO)
{
    // NDC xyz [-1,1]
    float vertices[] = {
        -0.5f,-0.5f,0.0f,       // left
         0.5f,-0.5f,0.0f,       // right
         0.0f, 0.5f,0.0f,       // top
    };
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
        }
        // unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    // unbind VAO
    glBindVertexArray(0);
    
}
