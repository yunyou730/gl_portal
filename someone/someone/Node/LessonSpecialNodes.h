#pragma once

#include "Ayy.h"

class Lesson15BoxNode : public ayy::CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lesson15PlaneNode : public ayy::CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};


class Lesson15BorderNode : public ayy::CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lesson15WindowNode : public ayy::CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};


class Lesson16PostProcessNode : public ayy::CommonNode
{
public:
    int postProcessIndex = 0;
    float blurFactor = 1.0f;
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lessin18ReflectNode : public ayy::CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lesson19ModelNode : public ayy::CommonNode
{
public:
    Lesson19ModelNode(const std::string& modelPath,const std::string& prefixPath);
    virtual ~Lesson19ModelNode();
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    virtual void OnRender(ayy::Camera* mainCam) override;
protected:
    ayy::model::Model* _model = nullptr;

};

class Lesson20NormalMapNode : public ayy::CommonNode
{
public:
    void SetNormalMapEnable(bool bEnable) {_bEnableNormalmap = bEnable;}
    
    void SetPointLightPos(const ayy::Vec3f& pos) {_pointLightPos = pos;}
    void SetPointLightAmbient(const ayy::Vec3f& ambient) {_pointLightAmbient = ambient;}
    void SetPointLightDiffuse(const ayy::Vec3f& diffuse) {_pointLightDiffuse = diffuse;}
    void SetPointLightSpecular(const ayy::Vec3f& specular) {_pointLightSpecular = specular;}
    void SetPointLightFactors(float constant,float linear,float quadratic)
    {
        _pointLightConstant = constant;
        _pointLightLinear = linear;
        _pointLightQuadratic = quadratic;
    }
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
public:
    bool        _bEnableNormalmap = true;
    bool        _bEnableWrongNormalMap = false;
    
    ayy::Vec3f  _pointLightPos;
    ayy::Vec3f  _pointLightAmbient;
    ayy::Vec3f  _pointLightDiffuse;
    ayy::Vec3f  _pointLightSpecular;
    float       _pointLightConstant;
    float       _pointLightLinear;
    float       _pointLightQuadratic;
};

class Lesson21TestSDF : public ayy::CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};
