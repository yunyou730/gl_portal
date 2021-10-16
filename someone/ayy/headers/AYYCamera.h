#pragma once
#include <glad/glad.h>
#include <iostream>
#include "AYYMath.h"

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
    virtual ~Camera() {}
    void SetViewportSize(int width,int height) { _viewportWidth = width;_viewportHeight = height;}
    
    ayy::Mat4x4f& GetViewMatrix();
    ayy::Mat4x4f& GetProjMatrix();
    
    const ayy::Vec3f& GetLookDir() const { return _lookDir; }
    const ayy::Vec3f& GetRightDir() const { return _rightDir; }
    const ayy::Vec3f& GetUpDir() const { return _upDir; }
    
    void SetPos(const ayy::Vec3f& pos);
    ayy::Vec3f GetPos() const { return _eye; }
    
    void SetLookDir(const ayy::Vec3f& lookDir);
    
    void TakeMove(float deltaX,float deltaY,float deltaZ);
    void TakeRot(float deltaDegX,float deltaDegY,float deltaDegZ);
    
    // rot by local x
    void TakePitch(float deltaDeg);
    // rot by local y
    void TakeYaw(float deltaDeg);
    // rot by local z
    void TakeRoll(float deltaDeg);
    
    // rot by world y
    void TakeHeading(float deltaDeg);
    
    float GetFov() const { return _fov;}
    float GetFar() const { return _far;}
    float GetNear() const { return _near;}
    
    void SetNear(float near) { _near = near;}
    void SetFar(float far) {_far = far;}
    
    void Dump() const;
    
protected:
    void CalcViewMatrix();
    void CalcLocalDirByLookDir();
    void CalcLocalAxis();
    
protected:
    ECamProjMode    _mode;
    
    
    ayy::Vec3f      _eye;
    
    ayy::Vec3f      _lookDir;       // local z
    ayy::Vec3f      _rightDir;      // local x
    ayy::Vec3f      _upDir;         // local y
    
    ayy::Mat4x4f    _viewMat;
    bool            _bViewMatDirty = true;
    
    ayy::Mat4x4f    _projMat;
    bool            _bProjMatDirty = true;
    
    int     _viewportWidth,_viewportHeight;
    float   _fov;
    float   _far;
    float   _near;
    
    float   _pitch = 0;
    float   _yaw = 0;
    float   _roll = 0;
    
    
    ayy::Vec3f _baseLookDir;
    ayy::Vec3f _baseRightDir;
    ayy::Vec3f _baseUpDir;
};

}

