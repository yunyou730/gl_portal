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
    
    const ayy::Vec3f& GetLookDir() const { return _lookDir; }
    const ayy::Vec3f& GetLeftDir() const { return _leftDir; }
    const ayy::Vec3f& GetUpDir() const { return _upDir; }
    
    void SetLookTarget(const ayy::Vec3f& lookTarget);
    void SetLookDir(const ayy::Vec3f& lookDir);
    
    void SetPos(const ayy::Vec3f& pos);
    void SetEuler(float byX,float byY,float byZ);
    
    void TakeMove(float deltaX,float deltaY,float deltaZ);
    void TakeRot(float deltaDegX,float deltaDegY,float deltaDegZ);
    
    // rot by local x
    void TakePitch(float deltaDeg);
    // rot by local y
    void TakeYaw(float deltaDeg);
    // rot by local z
    void TakeRoll(float deltaDeg);
    
    float GetFov() const { return _fov;}
    float GetFar() const { return _far;}
    float GetNear() const { return _near;}
    
protected:
    void CalcViewMatrix();
    void CalcLocalDirByLookDir();
protected:
    ECamProjMode    _mode;
    
    
    ayy::Vec3f      _eye;
    
    ayy::Vec3f      _lookDir;       // local z
    ayy::Vec3f      _leftDir;      // local x
    ayy::Vec3f      _upDir;         // local y
    
    ayy::Mat4x4f    _viewMat;
    bool            _bViewMatDirty = true;
    
    ayy::Mat4x4f    _projMat;
    bool            _bProjMatDirty = true;
    
    int     _viewportWidth,_viewportHeight;
    float   _fov;
    float   _far;
    float   _near;
};

}

