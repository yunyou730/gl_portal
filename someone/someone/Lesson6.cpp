#include "Lesson6.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "stb_image.h"
#include "RawTexture.h"
#include "Texture.h"

const int kIndiceCount = 6;

Lesson6::~Lesson6()
{
    
}

void Lesson6::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/color_texture.vs", "res/color_texture.fs");
    PrepareMesh(_vao,_vbo,_ebo);
    PrepareTexture();
}

void Lesson6::Cleanup()
{
    delete _shader;
    _shader = nullptr;
    
    if(_texture != nullptr)
    {
        delete _texture;
        _texture = nullptr;
    }
    
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
    

}

void Lesson6::OnUpdate()
{
    // using shader
    _shader->Use();
    // using texture
    glUniform1i(glGetUniformLocation(_shader->program,"myTex"),0);
    
    _texture->Bind();
    // draw with VAO
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,kIndiceCount,GL_UNSIGNED_INT,(void*)0);
    
    glBindVertexArray(0);
    _shader->UnUse();
    _texture->UnBind();
}

void Lesson6::PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO)
{
    // rectangle
    float vertices[] = {
        -0.5f,-0.5f,0.0f,       // left bottom pos
         1.0f, 0.0f,0.0f,       // red
         0.0f, 0.0f,            // uv
        
        -0.5f, 0.5f,0.0f,       // left top
         0.0f, 1.0f,0.0f,       // green
         0.0f, 1.0f,            // uv
        
         0.5f,-0.5f,0.0f,       // right bottom
         0.0f, 0.0f,1.0f,       // blue
         1.0f, 0.0f,            // uv
        
         0.5f, 0.5f,0.0f,       // right top
         1.0f, 1.0f,0.0f,       // yellow
         1.0f, 1.0f,            // uv
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
            
            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,color data
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);
            
            // attribute location 2,uv data
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
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

void Lesson6::PrepareTexture()
{
    ayy::RawTexture rawTexture("res/container.jpg");
    _texture = new ayy::Texture(&rawTexture);
}
