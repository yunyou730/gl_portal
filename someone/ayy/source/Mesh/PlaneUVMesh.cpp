#include "../../headers/Mesh/PlaneUVMesh.h"


static const float kSideLen = 1.0f;
static const float kPosY = 0.0f;

namespace ayy {
PlaneUVMesh::PlaneUVMesh()
{
    
}

PlaneUVMesh::~PlaneUVMesh()
{
    
}

void PlaneUVMesh::Prepare()
{
    float vertices[] = {
                0,          kPosY, 0,       // left back
                0,0, // uv
                
                0,          kPosY, kSideLen,        // left front
                0,1,
        
                kSideLen,   kPosY, 0,        // right back
                1,0,
        
                kSideLen,   kPosY, kSideLen,        // right front
                1,1
    };
    
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
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
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}

void PlaneUVMesh::Cleanup()
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

void PlaneUVMesh::Draw()
{
    GLsizei indiceCount = GetIndexCount();
    glDrawElements(GL_TRIANGLES,indiceCount,GL_UNSIGNED_INT,(void*)0);
}

void PlaneUVMesh::Bind()
{
    glBindVertexArray(_vao);
}

void PlaneUVMesh::UnBind()
{
    glBindVertexArray(0);
}

int PlaneUVMesh::GetIndexCount()
{
    return 6;
}

}
