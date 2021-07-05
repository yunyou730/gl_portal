#pragma once

#include "BaseMaterial.h"

class PhongTexMaterial : public BaseMaterial
{
public:
    virtual void SyncShaderParam() override;
    
    // light
    void SetLightPos(const ayy::Vec3f& lightPos);
    
    // object
    void SetDiffuseTexture(ayy::TextureUUID texId) { _texDiffuse = texId;}
    void SetSpecularTexture(ayy::TextureUUID texId) { _texSpecular = texId;}
    void SetSpecularShininess(float shininess) {_shininess = shininess;}
    
protected:
    ayy::TextureUUID _texDiffuse;
    ayy::TextureUUID _texSpecular;
    float       _shininess = 32.0f;
};
