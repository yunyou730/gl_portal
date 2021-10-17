#include "BlockBatchRender.h"

namespace crude {

BlockBatchRender::BlockBatchRender()
{
    
}

BlockBatchRender::~BlockBatchRender()
{
    
}

void BlockBatchRender::Initiate()
{
    PrepareMesh();
    _shader = ayy::Util::CreateShaderWithFile("res/demo/block_instance.vs","res/demo/block_instance.fs");
}

void BlockBatchRender::CleanUp()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_vboOffset);
    glDeleteBuffers(1,&_ebo);
    
    AYY_SAFE_DEL(_shader);
}

void BlockBatchRender::OnUpdate(float deltaTime)
{
    
}

void BlockBatchRender::OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix)
{
    ayy::Mat4x4f scaleMatrix;
    scaleMatrix.Identify();
    ayy::MakeScaleMatrix(scaleMatrix,_scale);
    
    _shader->Use();
    _shader->SetUniformMat4x4("u_Model",(GLfloat*)worldMatrix->data);
    _shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    _shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    _shader->SetUniformMat4x4("u_ScaleMat",(GLfloat*)scaleMatrix.data);
//    _shader->SetUniform("u_Scale",_scale);
    
    if(IsDirty())
    {
        RefreshInstanceData();
        SetDirty(false);
    }
    
    glBindVertexArray(_vao);
    glDrawElementsInstanced(GL_TRIANGLES,36,GL_UNSIGNED_INT,(void*)0,(GLsizei)_instanceDatas.size());
    glBindVertexArray(0);
    _shader->UnUse();
}

void BlockBatchRender::PrepareMesh()
{
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
    glGenBuffers(1,&_vboOffset);
    
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
        
        // vbo offset
        glBindBuffer(GL_ARRAY_BUFFER,_vboOffset);
        {
//            glBufferData(GL_ARRAY_BUFFER,sizeof(ayy::Vec2f) * offsets.size(),&offsets[0],GL_STATIC_DRAW);
//            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, 0,0);
//            glEnableVertexAttribArray(2);
            // offset data
            glBufferData(GL_ARRAY_BUFFER,sizeof(ayy::Vec3f) * _instanceDatas.size(),&_instanceDatas[0],GL_DYNAMIC_DRAW);
            // attribute location 1,offset data
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glVertexAttribDivisor(1,1);     // instance for each drawing
        
        // ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    
    glBindVertexArray(0);
}

void BlockBatchRender::AddDrawInstance(const ayy::Vec3f& offset)
{
    _instanceDatas.push_back(offset);
    SetDirty(true);
}

void BlockBatchRender::ModifyDrawInstance(int index,const ayy::Vec3f& offset)
{
    if(index >= 0 && index < _instanceDatas.size())
    {
        _instanceDatas[index] = offset;
    }
    SetDirty(true);
}

void BlockBatchRender::RefreshInstanceData()
{
    // only update vbo offset
    glBindVertexArray(_vao);
    {
        // vbo offset
        glBindBuffer(GL_ARRAY_BUFFER,_vboOffset);
        glCheckError();
        {
            // offset data
            glBufferData(GL_ARRAY_BUFFER,sizeof(ayy::Vec3f) * _instanceDatas.size(),&_instanceDatas[0],GL_DYNAMIC_DRAW);
            glCheckError();

            // attribute location 1,offset data
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
            glCheckError();

            glEnableVertexAttribArray(1);
            glCheckError();
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
//        glVertexAttribDivisor(1,1);     // instance for each drawing
    }
    glBindVertexArray(0);
    glCheckError();
}


}


