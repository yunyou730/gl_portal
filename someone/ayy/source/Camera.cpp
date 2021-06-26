#include "Camera.h"

namespace ayy
{

/*
    default pos  (0,0,5)
    default look dir (0,0,-1,0) // w = 0 means vector is a direction
 */
const static ayy::Vec3f kWorldUpDir(0,1,0);
const static ayy::Vec3f kDefaultPos(0,0,5);

Camera::Camera(int viewportWidth,int viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
    ,_fov(45)
    ,_far(100.0f)
    ,_near(0.1f)
{
    _eye = kDefaultPos;
    
    _lookDir = ayy::Vec3f(0,0,-1);
    CalcLocalDirByLookDir();
    
    _viewMat.Identify();
    _projMat.Identify();
}

Mat4x4f& Camera::GetViewMatrix()
{
    if(_bViewMatDirty)
    {
        _bViewMatDirty = false;
        CalcViewMatrix();
    }
    return _viewMat;
}

void Camera::CalcViewMatrix()
{
    ayy::Vec3f z,x,y;   // camera z,x,y (forward,right,up)
    
    z = _lookDir;
    x = _leftDir;
    y = _upDir;
    
    _viewMat.Identify();
    _viewMat.Set(0,0,x.x());    _viewMat.Set(1,0,x.y());    _viewMat.Set(2,0,x.z());
    _viewMat.Set(0,1,y.x());    _viewMat.Set(1,1,y.y());    _viewMat.Set(2,1,y.z());
    _viewMat.Set(0,2,z.x());    _viewMat.Set(1,2,z.y());    _viewMat.Set(2,2,z.z());
    _viewMat.Set(3,0,_eye.Dot(x));
    _viewMat.Set(3,1,_eye.Dot(y));
    _viewMat.Set(3,2,_eye.Dot(z));
}

void Camera::TakeMove(float deltaX,float deltaY,float deltaZ)
{
    _eye.SetX(_eye.x() + deltaX);
    _eye.SetY(_eye.y() + deltaY);
    _eye.SetZ(_eye.z() + deltaZ);
    _bViewMatDirty = true;
}

/*
 更新 look dir
*/
void Camera::TakeRot(float deltaDegX,float deltaDegY,float deltaDegZ)
{
    ayy::Mat4x4f rotX,rotY,rotZ;
    ayy::MakeRotateByXMatrix(rotX,ayy::DegToRad(deltaDegX));
    ayy::MakeRotateByYMatrix(rotY,ayy::DegToRad(deltaDegY));
    ayy::MakeRotateByZMatrix(rotZ,ayy::DegToRad(deltaDegZ));
    
    _lookDir.Normalize();
    
    ayy::Vec4f tempDir(_lookDir.x(),_lookDir.y(),_lookDir.z(),0.0f);
    tempDir = tempDir * rotY * rotX * rotZ;
    tempDir.Normalize();
    
    _lookDir.SetX(tempDir.x());
    _lookDir.SetY(tempDir.y());
    _lookDir.SetZ(tempDir.z());
    _lookDir.Normalize();
    CalcLocalDirByLookDir();
    
    _bViewMatDirty = true;
}


// rot by local x
void Camera::TakePitch(float deltaDeg)
{
    ayy::Mat4x4f rot;
    ayy::MakeRotateByAxisMatrix(rot,_leftDir,ayy::DegToRad(deltaDeg));
    
    _lookDir.Normalize();
    
    ayy::Vec4f tempDir(_lookDir.x(),_lookDir.y(),_lookDir.z(),0.0f);
    tempDir = tempDir * rot;
    tempDir.Normalize();
    
    _lookDir.SetX(tempDir.x());
    _lookDir.SetY(tempDir.y());
    _lookDir.SetZ(tempDir.z());
    _lookDir.Normalize();
    CalcLocalDirByLookDir();
    
    _bViewMatDirty = true;
}
// rot by local y
void Camera::TakeYaw(float deltaDeg)
{
    ayy::Mat4x4f rot;
    ayy::MakeRotateByAxisMatrix(rot,_upDir,ayy::DegToRad(deltaDeg));
    
    _lookDir.Normalize();
    
    ayy::Vec4f tempDir(_lookDir.x(),_lookDir.y(),_lookDir.z(),0.0f);
    tempDir = tempDir * rot;
    tempDir.Normalize();
    
    _lookDir.SetX(tempDir.x());
    _lookDir.SetY(tempDir.y());
    _lookDir.SetZ(tempDir.z());
    _lookDir.Normalize();
    CalcLocalDirByLookDir();
    
    _bViewMatDirty = true;
}

// rot by local z
void Camera::TakeRoll(float deltaDeg)
{
    ayy::Mat4x4f rot;
    ayy::MakeRotateByAxisMatrix(rot,_lookDir,ayy::DegToRad(deltaDeg));
    
    _lookDir.Normalize();
    
    ayy::Vec4f tempDir(_lookDir.x(),_lookDir.y(),_lookDir.z(),0.0f);
    tempDir = tempDir * rot;
    tempDir.Normalize();
    
    _lookDir.SetX(tempDir.x());
    _lookDir.SetY(tempDir.y());
    _lookDir.SetZ(tempDir.z());
    _lookDir.Normalize();
    CalcLocalDirByLookDir();
    
    _bViewMatDirty = true;
}

void Camera::SetLookTarget(const ayy::Vec3f& lookTarget)
{
    _lookDir = (lookTarget - _eye).Normalize();
    assert(_lookDir.Length() > 0);
    CalcLocalDirByLookDir();
    _bViewMatDirty = true;
}

void Camera::SetLookDir(const ayy::Vec3f& lookDir)
{
    if(lookDir.Length() > 0)
    {
        _lookDir = lookDir.GetNormalize();
        CalcLocalDirByLookDir();
        _bViewMatDirty = true;
    }
}

ayy::Mat4x4f& Camera::GetProjMatrix()
{
    if(_bProjMatDirty)
    {
        float cotangent = 1.0f / tan(DegToRad(GetFov() * 0.5f));
        float aspect = (float)_viewportWidth / (float)_viewportHeight;
        
        _projMat.Identify();
        
        _projMat.Set(0,0,cotangent / aspect);
        _projMat.Set(1,1,cotangent);
        _projMat.Set(2,2,-1.f * (GetFar() + GetNear())/(GetFar() - GetNear()));
        _projMat.Set(3,2,-1 * (2 * GetNear() * GetFar())/(GetFar() - GetNear()) );
        _projMat.Set(2,3,-1.f);
        _projMat.Set(3,3,0);
    }
    return _projMat;
}

void Camera::CalcLocalDirByLookDir()
{
    _leftDir = _lookDir.Cross(kWorldUpDir).Normalize();
    _upDir = _leftDir.Cross(_lookDir).Normalize();
}

}
