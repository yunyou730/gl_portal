#pragma once

#include "Ayy.h"
#include "PhongMultiLightMaterial.h"

namespace ayy
{
namespace model
{
class Model;
}
}

class ModelNode : public ayy::CommonNode
{
public:
    ModelNode(const std::string& modelPath,const std::string& modelPrefixPath);
    virtual ~ModelNode();
    
    virtual void OnRender(ayy::Camera* mainCam) override;
    
    void SetDirLight(const DirectionLight& dirLight);
    void SetPointLight(const PointLight& pointLight);
    void SetSpotLight(const SpotLight& spotLight);
    void SetShininess(float shininess);
    
    void SetDirLightEnable(bool bEnable) { _bEnableDirLight = bEnable;}
    void SetPointLightEnable(bool bEnable) { _bEnablePointLight = bEnable;}
    void SetSpotLightEnable(bool bEnable) { _bEnableSpotLight = bEnable;}
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
protected:
    ayy::model::Model*              _model = nullptr;
    
    DirectionLight  _dirLight;
    PointLight      _pointLight;
    SpotLight       _spotLight;
    float           _shininess = 0;
    
    bool _bEnableDirLight       = true;
    bool _bEnablePointLight     = true;
    bool _bEnableSpotLight      = true;
};
