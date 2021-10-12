
#include "Ground.h"

namespace crude {

Ground::Ground()
{
    
}

Ground::~Ground()
{
    CleanUp();
}

void Ground::Initiate()
{
    PrepareMesh();
    _shader = ayy::Util::CreateShaderWithFile("res/demo/ground.vs","res/demo/ground.fs");
}

void Ground::CleanUp()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
    _vao = 0;
    _vbo = 0;
    _ebo = 0;
    AYY_SAFE_DEL(_shader);
}

void Ground::OnUpdate(float deltaTime)
{
    
}

void Ground::OnDraw(ayy::Camera* camera)
{
    _shader->Use();
    ayy::Mat4x4f model;
    model.Identify();
    
    _shader->SetUniformMat4x4("u_Model",(GLfloat*)model.data);
    _shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    _shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
    
    _shader->UnUse();
}

void Ground::PrepareMesh()
{
    /*
     **/
    float vertices[] = {
        
        -1.0f, 0.0f, 1.0f,
//         0.0f, 0.0f,
        
        
        -1.0f, 0.0f,-1.0f,
//         0.0f, 1.0f,
        
         1.0f, 0.0f, 1.0f,
//         1.0f, 0.0f,
        
         1.0f, 0.0f,-1.0f,
//         1.0f, 1.0f,
    };
    
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
    };
    
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);
    
    // vao
    glBindVertexArray(_vao);
    {
        // vbo
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
//            // attribute location 1,color data
//            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(2* sizeof(float)));
//            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    
    glBindVertexArray(0);
    
}


}


