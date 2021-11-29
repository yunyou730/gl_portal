#pragma once

#include "Define.h"
#include "BaseComponent.h"
#include "Ayy.h"
#include "ModelImporter.h"

namespace crude {

class ModelComponent : public BaseComponent
{
public:
    ModelComponent();
    virtual ~ModelComponent();
    
    void Load(const std::string& filePath,const std::string& prefixPath);
    ayy::model::Model* GetModel() { return _model;}
    ayy::meshv2::Model* GetModel2() { return _model2;}
    
protected:
    ayy::model::Model*  _model = nullptr;
    ayy::meshv2::Model* _model2 = nullptr;
};
}
