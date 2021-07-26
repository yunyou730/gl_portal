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

