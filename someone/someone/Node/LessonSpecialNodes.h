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
