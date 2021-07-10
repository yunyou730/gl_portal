#pragma once

#include "BaseMaterial.h"
#include "Math.h"

typedef enum
{
    ELightType_Direction,
    ELightType_Point,
    ELightType_Spot,
    
    ELightType_Max,
} ELightType;

class DirectionLight
{
public:
    ayy::Vec3f direction = ayy::Vec3f(-1,-1,-1);
    
    ayy::Vec3f ambient = ayy::Vec3f(0.1f,0.1f,0.1f);     // color of ambient
    ayy::Vec3f diffuse = ayy::Vec3f(0.2f,0.2f,0.2f);     // color of diffuse
    ayy::Vec3f specular = ayy::Vec3f(0.3f,0.3f,0.3f);    // color of specular
    
    void operator =(const DirectionLight& other)
    {
        direction = other.direction;
        
        ambient = other.ambient;
        diffuse = other.diffuse;
        specular = other.specular;
    }
};

class PointLight
{
public:
    ayy::Vec3f position = ayy::Vec3f(0.0f,0.0f,0.0f);
    
    float constant = 1.0f;
    float linear = 0.045f;
    float quadratic = 0.0075f;
    
    ayy::Vec3f ambient = ayy::Vec3f(0.2f,0.2f,0.2f);     // color of ambient
    ayy::Vec3f diffuse = ayy::Vec3f(0.5f,0.5f,0.5f);     // color of diffuse
    ayy::Vec3f specular = ayy::Vec3f(1.0f,1.0f,1.0f);    // color of specular
    
    
    void operator =(const PointLight& other)
    {
        position = other.position;
        constant = other.constant;
        linear = other.linear;
        quadratic = other.quadratic;
        
        ambient = other.ambient;
        diffuse = other.diffuse;
        specular = other.specular;
    }
};

class SpotLight
{
public:
    ayy::Vec3f position = ayy::Vec3f(0.0f,0.0f,0.0f);
    ayy::Vec3f direction = ayy::Vec3f(0.0f,0.0f,-1.0f);
    float deg = 5.5f;
    float outerDeg = 7.5f;
    
    ayy::Vec3f ambient = ayy::Vec3f(0.2f,0.2f,0.2f);     // color of ambient
    ayy::Vec3f diffuse = ayy::Vec3f(0.5f,0.5f,0.5f);     // color of diffuse
    ayy::Vec3f specular = ayy::Vec3f(1.0f,1.0f,1.0f);    // color of specular
    
    
    void operator =(const SpotLight& other)
    {
        position = other.position;
        direction = other.direction;
        deg = other.deg;
        outerDeg = other.outerDeg;
        
        ambient = other.ambient;
        diffuse = other.diffuse;
        specular = other.specular;
    }
};

class PhongMultiLightMaterial : public BaseMaterial
{
public:
    virtual void SyncShaderParam() override;
    
    void SetLightType(ELightType lightType) { _lightType = lightType;}
    
    void SetSpotLightParam(const SpotLight& spotLightParam) { _spotLightParam = spotLightParam;}
    void SetDirectionLightParam(const DirectionLight& dirLightParam) { _dirLightParam = dirLightParam;}
    void SetPosLightParam(const PointLight& pointLightParam) { _pointLightParam = pointLightParam;}
    
    DirectionLight& GetDirLightParam() { return _dirLightParam;}
    PointLight& GetPointLightParam() { return _pointLightParam;}
    SpotLight& GetSpotLightParam() { return _spotLightParam;}
    
    void SetTexture(ayy::TextureUUID texDiffuse,ayy::TextureUUID texSpecular);
    void SetSpecularShininess(float shininess);
        
    void SetDirLightEnable(bool bEnable) { _bEnableDirLight = bEnable;}
    void SetPointLightEnable(bool bEnable) { _bEnablePointLight = bEnable;}
    void SetSpotLightEnable(bool bEnable) { _bEnableSpotLight = bEnable;}
    
protected:
    ayy::TextureUUID    _texDiffuse = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID    _texSpecular = ayy::TextureManager::kInvalidTextureUUID;
    float               _shininess = 32.0f;
    
    ELightType  _lightType = ELightType::ELightType_Spot;
    
    DirectionLight  _dirLightParam;
    PointLight      _pointLightParam;
    SpotLight       _spotLightParam;
    
    bool _bEnableDirLight = true;
    bool _bEnablePointLight = true;
    bool _bEnableSpotLight = true;
};
