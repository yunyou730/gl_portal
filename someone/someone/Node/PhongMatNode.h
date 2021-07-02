#pragma once

#include "CommonNode.h"

class PhongMaterial;
class PhongMatNode : public CommonNode
{
public:
    PhongMatNode();
    virtual ~PhongMatNode();
    
    virtual void SetShader(ayy::ShaderProgram* shader) override;
    
    void SetViewPos(const ayy::Vec3f& viewPos);
    void SetMaterial(const ayy::Vec3f& ambient,const ayy::Vec3f& diffuse,const ayy::Vec3f& specular,float shininess);
    void SetLight(const ayy::Vec3f& ambient,const ayy::Vec3f& diffuse,const ayy::Vec3f& specular);
    
    void SetLightSourcePos(const ayy::Vec3f& lightPos) { _lightSourcePos = lightPos;}
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
private:
    ayy::Vec3f  _lightSourcePos;
    ayy::Vec3f  _viewPos;
    
    ayy::Vec3f  _lightAmbient;
    ayy::Vec3f  _lightDiffuse;
    ayy::Vec3f  _lightSpecular;
    
    PhongMaterial*  _material = nullptr;
};
