#pragma once
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"


namespace ayy {

class ShaderProgram;
class Camera;
namespace model
{

class Model
{
public:
    Model();
    ~Model();
    
    void Load(const std::string& path,const std::string& prefixPath);
    void Draw(ayy::ShaderProgram* shader);
    void DoDraw();
    
    void SetIgnoreTexture(bool bIgnoreTexture) { _bIgnoreTexture = bIgnoreTexture;}
protected:
    bool IsIgnoreTexture() const { return _bIgnoreTexture;}
    
protected:
    void processNode(aiNode* node,const aiScene* scene);
    ayy::model::Mesh* processAndCreateMesh(aiMesh* mesh,const aiScene* scene);
    std::vector<ayy::model::Texture> loadMaterialTextures(aiMaterial* mat,aiTextureType type,const std::string& typeName);
private:
    std::vector<ayy::model::Mesh*>  _meshes;
    std::string _directory;
    std::string _prefixPath;
    
    bool _bIgnoreTexture = false;
    
};
}


}
