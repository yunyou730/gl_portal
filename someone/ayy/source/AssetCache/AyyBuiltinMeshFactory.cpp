#include "../../headers/AssetCache/AyyBuiltinMeshFactory.h"

namespace ayy
{

void BuiltinMeshFactory::Init()
{
    _builtinMeshes.insert(std::make_pair("ayy/builtin/quad", CreeateQuad()));
}

void BuiltinMeshFactory::Cleanup()
{
    
}

BuiltinMesh* BuiltinMeshFactory::GetBuiltinMesh(const std::string& virtualPath)
{
    auto it = _builtinMeshes.find(virtualPath);
    if(it != _builtinMeshes.end())
    {
        return it->second;
    }
    return nullptr;
}

BuiltinMesh* BuiltinMeshFactory::CreeateQuad()
{
    auto ret = new BuiltinMesh();
    
    // vertices data
    float vertices[] = {
        // pos x3, uv x2
         -1.0, -1.0, 0.0,   0.0,0.0,
         -1.0, 1.0, 0.0,    0.0,1.0,
         1.0, -1.0, 0.0,  1.0,0.0,
         1.0, 1.0, 0.0,  1.0,1.0
    };
    
    // indice data
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
    };
    
    // VAO & VBO
    glGenVertexArrays(1,&ret->vao);
    glGenBuffers(1,&ret->vbo);
    glGenBuffers(1,&ret->ebo);
    
    glBindVertexArray(ret->vao);
    {
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER,ret->vbo);
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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ret->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    
    // unbind VAO
    glBindVertexArray(0);
    
    
    // shader    // temp null
    
    return ret;
}

}

