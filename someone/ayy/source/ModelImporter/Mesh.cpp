#include "../../headers/ModelImporter/Mesh.h"
#include "../../headers/Shader.h"
#include "Ayy.h"

namespace ayy
{
namespace model
{

Mesh::Mesh(const std::vector<ayy::model::Vertex>& vertices,
           const std::vector<unsigned int>& indices,
           const std::vector<ayy::model::Texture>& textures)
{
    _vertices   = vertices;
    _indices    = indices;
    _textures   = textures;
    
    SetupMesh();
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
                 &_indices[0], GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    
    glBindVertexArray(0);
}

void Mesh::Draw(ayy::ShaderProgram* shader,ayy::Camera* camera)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < _textures.size(); i++)
    {
//        glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
        // @miao @todo
        TextureManager::GetInstance()->BindTextureToSlot(_textures[i].uuid, i);
        
        // 获取纹理序号（diffuse_textureN 中的 N）
        std::string number;
        std::string name = _textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        // @miao @todo
        shader->SetUniform("material." + name + number,(int)i);
//        glBindTexture(GL_TEXTURE_2D, _textures[i].uuid);
    }
//    glActiveTexture(GL_TEXTURE0);

    // 绘制网格
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


}
}
