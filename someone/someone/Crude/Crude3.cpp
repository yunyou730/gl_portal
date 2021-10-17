#include "Crude3.h"
#include <sstream>
#include "../Demo/FreeCamera.h"
#include "../Demo/ecs/Util.h"

Crude3::Crude3(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    
}

Crude3::~Crude3()
{
    
}

void Crude3::Prepare()
{
    _camera = new crude::FreeCamera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,3,5));
    _camera->SetLookDir(ayy::Vec3f(0,0,0) - _camera->GetPos());
    
    PrepareGroundMesh();
    PrepareBoxMesh();
    
    _groundShader = ayy::Util::CreateShaderWithFile("res/crude1/ground.vs","res/crude1/ground.fs");
    _boxShader = ayy::Util::CreateShaderWithFile("res/crude1/box.vs","res/crude1/box.fs");
    
    _groundTransform.SetScale(ayy::Vec3f(20.0,1.0,20.0));
    _groundTransform.SetPos(ayy::Vec3f(-5.0,0.0,-5.0));
    
    for(int i = 0;i < 5;i++)
    {
        crude::TransformComponent transform;
        int x = crude::Util::random(-4,4);
        int y = crude::Util::random(0,3);
        int z = crude::Util::random(-4,4);
        transform.SetPos(ayy::Vec3f(x,y,z));
        _boxes.push_back(transform);
    }
}

void Crude3::PrepareGroundMesh()
{
    // vertices data
    float vertices[] = {
        // pos x3, uv x2
         0.0, 0.0, 0.0,  0.0,0.0,
         0.0, 0.0, 1.0,  0.0,1.0,
         1.0, 0.0, 0.0,  1.0,0.0,
         1.0, 0.0, 1.0,  1.0,1.0
    };
    
    // indice data
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
    };
    
    // VAO & VBO
    glGenVertexArrays(1,&_groundVAO);
    glGenBuffers(1,&_groundVBO);
    glGenBuffers(1,&_groundEBO);
    
    glBindVertexArray(_groundVAO);
    {
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER,_groundVBO);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1, uv
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_groundEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    
    // unbind VAO
    glBindVertexArray(0);
}

void Crude3::PrepareBoxMesh()
{
    // vertices
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
    
    glGenVertexArrays(1,&_boxVAO);
    glGenBuffers(1,&_boxVBO);
    glGenBuffers(1,&_boxEBO);
    
    glBindVertexArray(_boxVAO);
    {
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER,_boxVBO);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_boxEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}

void Crude3::Cleanup()
{
    glDeleteVertexArrays(1,&_groundVAO);
    glDeleteVertexArrays(1,&_boxVAO);
        
    glDeleteBuffers(1,&_groundVBO);
    glDeleteBuffers(1,&_groundEBO);
    glDeleteBuffers(1,&_boxVBO);
    glDeleteBuffers(1,&_boxEBO);
    
    AYY_SAFE_DEL(_groundShader);
    AYY_SAFE_DEL(_boxShader);
    
    AYY_SAFE_DEL(_camera);
}

void Crude3::OnRender()
{
    DrawGround();
    DrawBoxes();
}

void Crude3::DrawGround()
{
    _groundShader->Use();
    
    _groundShader->SetUniformMat4x4("u_Model",(GLfloat*)_groundTransform.GetWorldMatrix()->data);
    _groundShader->SetUniformMat4x4("u_View",(GLfloat*)_camera->GetViewMatrix().data);
    _groundShader->SetUniformMat4x4("u_Projection",(GLfloat*)_camera->GetProjMatrix().data);
    
    glBindVertexArray(_groundVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
    _groundShader->UnUse();
}

void Crude3::DrawBoxes()
{
    _boxShader->Use();
    
    _boxShader->SetUniformMat4x4("u_View",(GLfloat*)_camera->GetViewMatrix().data);
    _boxShader->SetUniformMat4x4("u_Projection",(GLfloat*)_camera->GetProjMatrix().data);
    
    glBindVertexArray(_boxVAO);
    
    for(auto it : _boxes)
    {
        _boxShader->SetUniformMat4x4("u_Model",(GLfloat*)it.GetWorldMatrix()->data);
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,(void*)0);
    }
    
    _boxShader->UnUse();
}


void Crude3::HandleKeyboardInput(GLFWwindow* window)
{
    _camera->HandleKeyboardInput(window,GetDeltaTime());
}
