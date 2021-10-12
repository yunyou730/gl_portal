#include "Crude2.h"
#include <sstream>

#include "../Demo/FreeCamera.h"
#include "../Demo/Wall.h"
#include "../Demo/Ground.h"

Crude2::Crude2(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    
}

Crude2::~Crude2()
{
    
}

void Crude2::Prepare()
{
    _camera = new crude::FreeCamera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,1,1));
    _camera->SetLookDir(ayy::Vec3f(0,0,0) - ayy::Vec3f(0,1,1));
    
    PrepareMesh();
    
    _ground = new crude::Ground();
    _ground->Initiate();
    
    _wall = new crude::Wall();
    _wall->Initiate();
}

void Crude2::PrepareMesh()
{
    // vertices data
    float quadVertices[] = {
        // pos(float x2) ,  color(float x3)
        -0.05, 0.05,        1.0,0.0,0.0,        // left top
         0.05,-0.05,        0.0,1.0,0.0,        // right bottom
        -0.05,-0.05,        0.0,0.0,1.0,        // left bottom
        
        -0.05, 0.05,        1.0,0.0,0.0,        // left top
         0.05,-0.05,        0.0,1.0,0.0,        // right bottom
         0.05, 0.05,        0.0,1.0,1.0,        // right top
    };
    
    // offset data
    std::vector<ayy::Vec2f> offsets;
    float kOffset = 0.1f;
    for(int y = -10;y < 10;y += 2)
    {
        for(int x = -10;x < 10;x +=2)
        {
            ayy::Vec2f offset((float)x / 10.0f + kOffset,(float)y/10.0f + kOffset);
            offsets.push_back(offset);
        }
    }
    
    // VAO & VBO
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_vboOffset);
    
    glBindVertexArray(_vao);
    {
        // vbo1:  vertex pos & color
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),quadVertices,GL_STATIC_DRAW);

            // attribute location 0,pos data
            glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,color data
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(2* sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // vbo2 , vertex offset
        glBindBuffer(GL_ARRAY_BUFFER,_vboOffset);
        {
            // offset data
            glBufferData(GL_ARRAY_BUFFER,sizeof(ayy::Vec2f) * offsets.size(),&offsets[0],GL_STATIC_DRAW);

            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, 0,0);
            glEnableVertexAttribArray(2);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    glVertexAttribDivisor(2,1);     // !! important !
    
    // unbind VAO
    glBindVertexArray(0);
    
    // shader
    _shader = ayy::Util::CreateShaderWithFile("res/crude1/instance.vs","res/crude1/instance.fs");
}

void Crude2::Cleanup()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_vboOffset);
    AYY_SAFE_DEL(_shader);
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_ground);
    AYY_SAFE_DEL(_wall);
}

void Crude2::OnRender()
{
    _shader->Use();
    glBindVertexArray(_vao);
    glDrawArraysInstanced(GL_TRIANGLES,0,6,100);
    
    _ground->OnDraw(_camera);
    _wall->OnDraw(_camera);
}

void Crude2::HandleKeyboardInput(GLFWwindow* window)
{
    _camera->HandleKeyboardInput(window,GetDeltaTime());
}
