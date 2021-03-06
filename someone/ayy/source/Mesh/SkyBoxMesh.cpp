#include "../../headers/Mesh/SkyBoxMesh.h"

namespace ayy {

SkyBoxMesh::SkyBoxMesh()
    :_vao(0),_vbo(0),_ebo(0)
{
    
}

SkyBoxMesh::~SkyBoxMesh()
{

}

void SkyBoxMesh::Bind()
{
    glBindVertexArray(_vao);
}

void SkyBoxMesh::UnBind()
{
    glBindVertexArray(0);
}

int SkyBoxMesh::GetIndexCount()
{
    return _indexCount;
}

void SkyBoxMesh::Prepare()
{
    GLuint& VAO = _vao;
    GLuint& VBO = _vbo;
    GLuint& EBO = _ebo;
    
    // box
    float vertices[] = {
        // front
        -1.0f,-1.0f,1.0f,       // left bottom pos
        -1.0f, 1.0f,1.0f,       // left top
         1.0f,-1.0f,1.0f,       // right bottom
         1.0f, 1.0f,1.0f,       // right top
        
        // back
        -1.0f,-1.0f,-1.0f,       // left bottom pos
        -1.0f, 1.0f,-1.0f,       // left top
         1.0f,-1.0f,-1.0f,       // right bottom
         1.0f, 1.0f,-1.0f,       // right top
    };
    
    // rectangle indice
    unsigned int indices[] = {
        // front
        0,1,2,
        1,3,2,
        
        // back
        4,5,6,
        5,7,6,
        
        // left
        4,5,0,
        5,1,0,
        
        // right
        3,2,6,
        3,7,6,
        
        // top
        3,1,5,
        5,7,3,
        
        // bottom
        2,0,4,
        4,6,2,
    };
    
    _indexCount = sizeof(indices) / sizeof(indices[0]);
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            
            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
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

void SkyBoxMesh::Cleanup()
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

void SkyBoxMesh::Draw()
{
    GLsizei indiceCount = GetIndexCount();
    glDrawElements(GL_TRIANGLES,indiceCount,GL_UNSIGNED_INT,(void*)0);
}

}

