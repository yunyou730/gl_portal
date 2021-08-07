#pragma once

#include "CommonNode.h"

class Lesson15BoxNode : public CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lesson15PlaneNode : public CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};


class Lesson15BorderNode : public CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lesson15WindowNode : public CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};


class Lesson16PostProcessNode : public CommonNode
{
public:
    int postProcessIndex = 0;
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lessin18ReflectNode : public CommonNode
{
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
};

class Lesson19ModelNode : public CommonNode
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
