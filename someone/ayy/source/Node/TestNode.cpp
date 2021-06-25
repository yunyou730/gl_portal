#include "../../headers/Node/TestNode.h"

namespace ayy {

TestNode::TestNode()
    :_vao(0),_vbo(0),_ebo(0)
{
    
}

TestNode::~TestNode()
{

}

void TestNode::Bind()
{
    glBindVertexArray(_vao);
}

void TestNode::UnBind()
{
    glBindVertexArray(0);
}

int TestNode::GetIndexCount()
{
    return 18;
}

void TestNode::Prepare()
{
    GLuint& VAO = _vao;
    GLuint& VBO = _vbo;
    GLuint& EBO = _ebo;
    
    // rectangle
    float vertices[] = {
        // front
        -0.5f,-0.5f,0.5f,       // left bottom pos
         0.0f, 0.0f,            // uv
        
        -0.5f, 0.5f,0.5f,       // left top
         0.0f, 1.0f,            // uv
        
         0.5f,-0.5f,0.5f,       // right bottom
         1.0f, 0.0f,            // uv
        
         0.5f, 0.5f,0.5f,       // right top
         1.0f, 1.0f,            // uv
        
        
        // back
        -0.5f,-0.5f,-0.5f,       // left bottom pos
         0.0f, 0.0f,            // uv
        
        -0.5f, 0.5f,-0.5f,       // left top
         0.0f, 1.0f,            // uv
        
         0.5f,-0.5f,-0.5f,       // right bottom
         1.0f, 0.0f,            // uv
        
         0.5f, 0.5f,-0.5f,       // right top
         1.0f, 1.0f,            // uv
    };
    
    
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
        1,3,2,
        
        4,5,6,
        5,7,6,
        
        4,5,0,
        5,1,0,
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
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,uv data
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
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

void TestNode::Cleanup()
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

void TestNode::Draw()
{
    GLsizei indiceCount = GetIndexCount();
    glDrawElements(GL_TRIANGLES,indiceCount,GL_UNSIGNED_INT,(void*)0);
}

}

