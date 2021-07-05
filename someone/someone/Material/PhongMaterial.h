#pragma once

#include "BaseMaterial.h"

class PhongMaterial : public BaseMaterial
{
public:
    virtual void SyncShaderParam() override;
    
    // light
    void SetLightPos(const ayy::Vec3f& lightPos);
    
    // object
    void SetAmbientColor(const ayy::Vec3f& color);
    void SetDiffuseColor(const ayy::Vec3f& color);
    void SetSpecularColor(const ayy::Vec3f& color);
    void SetSpecularShininess(float shininess);
    
protected:
    ayy::Vec3f  _ambientColor;
    ayy::Vec3f  _diffuseColor;
    ayy::Vec3f  _specularColor;
    float       _shininess;
};
