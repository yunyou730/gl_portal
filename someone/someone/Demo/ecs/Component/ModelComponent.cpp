#include "ModelComponent.h"

namespace crude
{
ModelComponent::ModelComponent()
{
    _model = new ayy::model::Model();
    _model2 = new ayy::meshv2::Model();
}

ModelComponent::~ModelComponent()
{
    AYY_SAFE_DEL(_model);
    AYY_SAFE_DEL(_model2);
}

void ModelComponent::Load(const std::string& filePath,const std::string& prefixPath)
{
    _model->Load(filePath,prefixPath);
    
    ayy::meshv2::ModelImporter imp;
    _model2 = imp.CreateModel();
}

}

