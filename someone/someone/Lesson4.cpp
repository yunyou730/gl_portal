#include "Lesson4.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"

Lesson4::~Lesson4()
{
    
}

void Lesson4::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/test.vs", "res/test.fs");
    PrepareMesh(_vao,_vbo,_ebo);
    
    // uncomment this call to draw in wireframe polygons.
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void Lesson4::Cleanup()
{
    delete _shader;
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
}

void Lesson4::OnRender()
{
    _shader->Use();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Lesson4::PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO)
{
    // triangle
    float vertices[] = {
        -0.5f,-0.5f,0.0f,       // left bottom pos
         1.0f, 0.0f,0.0f,       // red
        
         0.0f, 0.5f,0.0f,       // mid top
         0.0f, 1.0f,0.0f,       // green
        
         0.5f,-0.5f,0.0f,       // right bottom
         0.0f, 0.0f,1.0f,       // blue
    };
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
    };
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            
            // attribute location 0,pos data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,color data
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);
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


