#pragma once

#include "AYYCommonNode.h"

class PhongNode : public ayy::CommonNode
{
public:
    void SetLightSourcePos(const ayy::Vec3f& lightSourcePos);
    void SetLightColor(const ayy::Vec3f& lightColor);
    void SetObjectColor(const ayy::Vec3f& color);
    void SetViewPos(const ayy::Vec3f& viewPos);
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    
private:
    ayy::Vec3f _lightSourcePos;
    ayy::Vec3f _lightColor;
    ayy::Vec3f _objectColor;
    ayy::Vec3f _viewPos;
};


