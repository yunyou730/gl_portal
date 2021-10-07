#include "Crude1.h"
#include <sstream>

Crude1::Crude1(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    
}

Crude1::~Crude1()
{
    
}

void Crude1::Prepare()
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
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    
    glBindVertexArray(_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            // data to buffer
            glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),quadVertices,GL_STATIC_DRAW);
            
            // explain each attribute
            
            // attribute location 0,pos data
            glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,color data
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(2* sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        // unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    // unbind VAO
    glBindVertexArray(0);
    
    
    // shader
    _shader = ayy::Util::CreateShaderWithFile("res/crude1/instance.vs","res/crude1/instance.fs");
    
    
    // offset data & pass to shader
        
    _shader->Use();
    float kOffset = 0.1f;
    int idx = 0;
    for(int y = -10;y < 10;y += 2)
    {
        for(int x = -10;x < 10;x +=2)
        {
            ayy::Vec2f offset((float)x / 10.0f + kOffset,(float)y/10.0f + kOffset);
            std::stringstream ss;
            ss << "u_offsets[" << idx << "]";
            std::string uniformName = ss.str();
            _shader->SetUniform(uniformName,offset);

            idx++;
        }
    }
    _shader->UnUse();
}

void Crude1::Cleanup()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    AYY_SAFE_DEL(_shader);
}

void Crude1::OnRender()
{
    _shader->Use();
    glBindVertexArray(_vao);
    glDrawArraysInstanced(GL_TRIANGLES,0,6,100);
}

