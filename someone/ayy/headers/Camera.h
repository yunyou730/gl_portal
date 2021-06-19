#pragma once
#include <glad/glad.h>
#include <iostream>
#include "Math.h"

namespace ayy {

class Camera
{
public:
    typedef enum
    {
        ORTHO,
        PROJECTION,
        
        MAX,
    } ECamProjMode;
    
public:
    Camera(int viewportWidth,int viewportHeight);
    
    ayy::Mat4x4f& GetViewMatrix();
    ayy::Mat4x4f& GetProjMatrix();
    
    const ayy::Vec3f& GetPos() const { return _pos;}
    const ayy::Vec3f& GetEuler() const { return _euler;}
    
    void SetPos(const ayy::Vec3f& pos);
    void SetEuler(float byX,float byY,float byZ);
    
    void TakeMove(float deltaX,float deltaY,float deltaZ);
    void TakeRot(float deltaDegX,float deltaDegY,float deltaDegZ);
    
    float GetFov() const { return _fov;}
    float GetFar() const { return _far;}
    float GetNear() const { return _near;}
    
protected:
    void CalcViewMatrix();
        
protected:
    ECamProjMode    _mode;
    
    ayy::Vec3f      _pos;
    ayy::Vec3f      _euler; // angle
    
    ayy::Mat4x4f    _viewMat;
    bool            _bViewMatDirty = true;
    
    ayy::Mat4x4f    _projMat;
    
    
    int     _viewportWidth,_viewportHeight;
    float   _fov;
    float   _far;
    float   _near;
};

}
