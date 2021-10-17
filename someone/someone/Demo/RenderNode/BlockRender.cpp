#include "BlockRender.h"
#include "../Manager/ShaderManager.h"

namespace crude {

BlockRender::BlockRender()
{
    
}

BlockRender::~BlockRender()
{
    
}

void BlockRender::Initiate()
{
    PrepareMesh();
    _shader = BaseManager::GetInstance<ShaderManager>()->LoadProgram("res/demo/block.vs","res/demo/block.fs");
}

void BlockRender::CleanUp()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
}

void BlockRender::OnUpdate(float deltaTime)
{
    
}

void BlockRender::OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix)
{
    _shader->Use();
    
    _shader->SetUniformMat4x4("u_Model",(GLfloat*)worldMatrix->data);
    _shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    _shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    _shader->UnUse();
}

void BlockRender::PrepareMesh()
{
    /*
     **/
    float vertices[] = {
        
        0.0,0.0,0.0,
//         0.0f, 0.0f,
        0.0,1.0,0.0,
//         0.0f, 1.0f,
        1.0,0.0,0.0,
//         1.0f, 0.0f,
        1.0,1.0,0.0,
//         1.0f, 1.0f,
        
        0.0,0.0,1.0,
//         0.0f, 0.0f,
        0.0,1.0,1.0,
//         0.0f, 1.0f,
        1.0,0.0,1.0,
//         1.0f, 0.0f,
        1.0,1.0,1.0,
    };
    
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
        
        4,5,6,
        6,5,7,
        
        4,5,0,
        0,5,1,
        
        2,3,6,
        6,3,7,
        
        3,1,7,
        7,1,5,
        
        4,0,6,
        6,0,2,
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


