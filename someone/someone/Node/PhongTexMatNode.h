#pragma once

#include "CommonNode.h"

class PhongTexMaterial;
class PhongTexMatNode : public CommonNode
{
public:
    PhongTexMatNode();
    virtual ~PhongTexMatNode();
    
    virtual void SetShader(ayy::ShaderProgram* shader) override;
    
    void SetViewPos(const ayy::Vec3f& viewPos);
    void SetLight(const ayy::Vec3f& ambient,const ayy::Vec3f& diffuse,const ayy::Vec3f& specular);
    void SetLightSourcePos(const ayy::Vec3f& lightPos) { _lightSourcePos = lightPos;}
    void SetMaterial(const ayy::TextureUUID& diffuseTex,const ayy::TextureUUID& specularTex,const float& shininess);
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
private:
    ayy::Vec3f  _lightSourcePos;
    ayy::Vec3f  _viewPos;
    
    ayy::Vec3f  _lightAmbient;
    ayy::Vec3f  _lightDiffuse;
    ayy::Vec3f  _lightSpecular;
    
    PhongTexMaterial*  _material = nullptr;
};
