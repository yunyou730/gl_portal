#include "../../headers/Mesh/PlaneMesh.h"


static const float kSideLen = 1.0f;
static const float kPosY = 0.0f;

namespace ayy {
PlaneMesh::PlaneMesh()
{
    
}

PlaneMesh::~PlaneMesh()
{
    
}

void PlaneMesh::Prepare()
{
    float vertices[] = {
                0,          kPosY, 0,       // left back
                0,          kPosY, kSideLen,        // left front
                kSideLen,   kPosY, 0,        // right back
                kSideLen,   kPosY, kSideLen,        // right front
    };
    
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
        2,3,1,
    };
    
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);
    
    glBindVertexArray(_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            
            // pos 0 , attribute pos
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}

void PlaneMesh::Cleanup()
{
    if(_vao > 0)
    {
        glDeleteVertexArrays(1,&_vao);
        _vao = 0;
    }
    
    if(_vbo > 0)
    {
        glDeleteBuffers(1,&_vbo);
        _vbo = 0;
    }
    
    if(_ebo > 0)
    {
        glDeleteBuffers(1,&_ebo);
        _ebo = 0;
    }
}

void PlaneMesh::Draw()
{
    GLsizei indiceCount = GetIndexCount();
    glDrawElements(GL_TRIANGLES,indiceCount,GL_UNSIGNED_INT,(void*)0);
}

void PlaneMesh::Bind()
{
    glBindVertexArray(_vao);
}

void PlaneMesh::UnBind()
{
    glBindVertexArray(0);
}

int PlaneMesh::GetIndexCount()
{
    return 6;
}

}
