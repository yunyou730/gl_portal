#include "../../headers/ModelImporter/Model.h"
#include <iostream>
#include "TextureManager.h"
#include "Camera.h"

namespace ayy
{

namespace model
{

Model::Model()
{
    
}

Model::~Model()
{
    for(auto it = _meshes.begin();it != _meshes.end();it++)
    {
        delete *it;
    }
    _meshes.clear();
}

void Model::Load(const std::string& path,const std::string& prefixPath)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));
    _prefixPath = prefixPath;
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node,const aiScene* scene)
{
    for(unsigned int i = 0;i < node->mNumMeshes;i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processAndCreateMesh(mesh,scene));
    }

    for(unsigned int i = 0;i < node->mNumChildren;i++)
    {
        processNode(node->mChildren[i],scene);
    }
}

ayy::model::Mesh* Model::processAndCreateMesh(aiMesh* mesh,const aiScene* scene)
{
    std::vector<ayy::model::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ayy::model::Texture> textures;
    
    // vertices. Position,Normals,UVs
    for(unsigned int i = 0;i < mesh->mNumVertices;i++)
    {
        ayy::model::Vertex v;
        
        v.Position = ayy::Vec3f(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);
        v.Normal = ayy::Vec3f(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);
        // only using the 1st uv temp
        if(mesh->mTextureCoords[0] != nullptr)
        {
            v.TexCoords = ayy::Vec2f(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
        }
        else
        {
            v.TexCoords = ayy::Vec2f(0,0);
        }
        vertices.push_back(v);
    }
    
    // indices.
    // 遍历每个面, 找到每个面 所有顶点的 索引，统一存储在 indices 里
    for(unsigned int i = 0;i < mesh->mNumFaces;i++)
    {
        aiFace* face = &mesh->mFaces[i];
        for(unsigned int j = 0;j < face->mNumIndices;j++)
        {
            indices.push_back(face->mIndices[j]);
        }
    }
    
    // material textures
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
        std::vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR,"texture_specular");
        textures.insert(textures.end(),diffuseMaps.begin(),diffuseMaps.end());
        textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
    }
    
    ayy::model::Mesh* result = new ayy::model::Mesh(vertices,indices,textures);
    return result;
}

std::vector<ayy::model::Texture> Model::loadMaterialTextures(aiMaterial* mat,aiTextureType type,const std::string& typeName)
{
    std::vector<ayy::model::Texture> textures;
    for(unsigned int i = 0;i < mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat->GetTexture(type,i,&str);
        
        
        Texture tex;
        tex.uuid = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath(_prefixPath + str.C_Str());
        assert(tex.uuid != ayy::TextureManager::kInvalidTextureUUID);
        
        tex.type = typeName;
        tex.path = str.C_Str();
        textures.push_back(tex);
    }
    return textures;
}

void Model::Draw(ayy::ShaderProgram* shader,ayy::Camera* camera)
{
    for(unsigned int i = 0;i < _meshes.size();i++)
    {
        _meshes[i]->Draw(shader,camera);
    }
}

}
}
