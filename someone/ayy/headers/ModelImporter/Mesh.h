#pragma once
#include <glad/glad.h>
#include <iostream>
#include "AYYMath.h"
#include <string>
#include <vector>
#include "AYYShader.h"

namespace ayy {

class Camera;
namespace model
{
struct Vertex
{
    ayy::Vec3f Position;
    ayy::Vec3f Normal;
    ayy::Vec2f TexCoords;
};

struct Texture
{
    unsigned int uuid;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(const std::vector<ayy::model::Vertex>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<ayy::model::Texture>& textures);
    
    ~Mesh();
    
    void Draw(ayy::ShaderProgram* shader);
    void DoDraw();
    
protected:
    void SetupMesh();
    void DeleteMesh();
    
    
public:
    std::vector<ayy::model::Vertex>     _vertices;
    std::vector<unsigned int>           _indices;
    std::vector<ayy::model::Texture>    _textures;
    
    GLuint  _VAO,_VBO,_EBO;
};

}

}

