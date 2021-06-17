#include "Lesson3.h"
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
uniform vec4 inputColor;
out vec4 FragColor;
void main()
{
    FragColor = inputColor;
}
)";

Lesson3::~Lesson3()
{
    
}

void Lesson3::Prepare()
{
    _shader = ayy::ShaderProgram::CreateShaderProgram(vsSource,fsSource);
    PrepareMesh(_vao,_vbo,_ebo);
    
    // uncomment this call to draw in wireframe polygons.
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void Lesson3::Cleanup()
{
    delete _shader;
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
}

void Lesson3::OnRender(float deltaTime)
{
    float t =glfwGetTime();
    

    _shader->Use();
    _shader->SetUniform("inputColor",ayy::Vec4f(sin(t),cos(t),sin(t),1.0));
    
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    
    
    glUseProgram(0);
}

void Lesson3::PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO)
{
    // rectangle
    float vertices[] = {
        -0.5f,-0.5f,0.0f,       // left bottom
        -0.5f, 0.5f,0.0f,       // left top
         0.5f,-0.5f,0.0f,       // right bottom
         0.5f, 0.5f,0.0f,       // right top
    };
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
        1,3,2,
    };
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
                
        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
    glBindVertexArray(0);
}


