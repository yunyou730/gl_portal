#pragma once
#include "AYYMesh.h"
#include <string>
#include "../../headers/ModelImporter/Model.h"

// @miao @todo
//  有问题 !
namespace ayy {
class ModelMesh : public AYYMesh
{
public:
    ModelMesh(const std::string& path,const std::string& prefixPath);
    virtual ~ModelMesh();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void Draw() override;
    
    void Bind() override;
    void UnBind() override;
    
    virtual int GetIndexCount() override;
    
protected:
//    GLuint  _vao,_vbo,_ebo;
    ayy::model::Model*  _model = nullptr;
    
    std::string _modelPath;
    std::string _modelPathPrefix;
    
};

}
