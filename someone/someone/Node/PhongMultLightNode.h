#pragma once

#include "CommonNode.h"

class PhongMultiLightMaterial;
class PhongMultLightNode : public ayy::CommonNode
{
public:
    PhongMultLightNode();
    virtual ~PhongMultLightNode();
    
    virtual void SetShader(ayy::ShaderProgram* shader) override;
    
    void SetLightSourcePos(const ayy::Vec3f& lightPos) { _lightSourcePos = lightPos;}
    
    PhongMultiLightMaterial* GetMaterial() { return _material; }
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
private:
    ayy::Vec3f  _lightSourcePos;
    ayy::Vec3f  _viewPos;
    
    PhongMultiLightMaterial*  _material = nullptr;
};
