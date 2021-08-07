#include "../../headers/Mesh/ModelMesh.h"
#include "Ayy.h"

namespace ayy {

ModelMesh::ModelMesh(const std::string& path,const std::string& prefixPath)
    :_modelPath(path)
    ,_modelPathPrefix(prefixPath)
{
    _model = new ayy::model::Model();
}

ModelMesh::~ModelMesh()
{
    Cleanup();
}

void ModelMesh::Prepare()
{
    _model->Load(_modelPath,_modelPathPrefix);
}

void ModelMesh::Cleanup()
{
    AYY_SAFE_DEL(_model);
}

void ModelMesh::Draw()
{
    
}

void ModelMesh::Bind()
{
    
}

void ModelMesh::UnBind()
{

}

int ModelMesh::GetIndexCount()
{
    return 0;
}

}
