#pragma once

#include "CommonNode.h"



namespace ayy
{
namespace model
{
class Model;
}
}

class ModelNode : public CommonNode
{
public:
    ModelNode(const std::string& modelPath,const std::string& modelPrefixPath);
    virtual ~ModelNode();
    
    virtual void OnRender(ayy::Camera* mainCam) override;
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
protected:
    ayy::model::Model*  _model = nullptr;
    
};


