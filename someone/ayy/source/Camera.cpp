#include "Camera.h"

namespace ayy
{

/*
    default pos  (0,0,5)
    default look dir (0,0,-1,0) // w = 0 means vector is a direction
 */
const static ayy::Vec3f kUpDir(0,1,0);
const static ayy::Vec3f kDefaultPos(0,0,5);
const static ayy::Vec4f kDefaultLookDir(0,0,-1,0);

Camera::Camera(int viewportWidth,int viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
    ,_fov(45)
    ,_far(10.0f)
    ,_near(0.1f)
{
    _eye = kDefaultPos;
    _center = ayy::Vec3f(0,0,0);
    
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
    
    z = (_center - _eye).Normalize();
    x = z.Cross(kUpDir).Normalize();
    y = x.Cross(z).Normalize();
    
    ayy::Mat4x4f matRot;
    ayy::Mat4x4f matMove;
    
    matRot.Identify();
    matMove.Identify();
    
    matRot.Set(0,0,x.x());    matRot.Set(1,0,x.y());    matRot.Set(2,0,x.z());
    matRot.Set(0,1,y.x());    matRot.Set(1,1,y.y());    matRot.Set(2,1,y.z());
    matRot.Set(0,2,z.x());    matRot.Set(1,2,z.y());    matRot.Set(2,2,z.z());
    
    matMove.Set(3,0,-_eye.x());    matMove.Set(3,1,-_eye.y());    matMove.Set(3,2,-_eye.z());
    
    _viewMat = matRot * matMove;
}

void Camera::TakeMove(float deltaX,float deltaY,float deltaZ)
{
    _eye.SetX(_eye.x() + deltaX);
    _eye.SetY(_eye.y() + deltaY);
    _eye.SetZ(_eye.z() + deltaZ);
    _bViewMatDirty = true;
}

void Camera::TakeRot(float deltaDegX,float deltaDegY,float deltaDegZ)
{
//    ayy::Mat4x4f rotX,rotY,rotZ;
//
//    _rotEuler.SetX(_rotEuler.x() + deltaDegX);
//    _rotEuler.SetY(_rotEuler.y() + deltaDegY);
//    _rotEuler.SetZ(_rotEuler.z() + deltaDegZ);
//
//    ayy::MakeRotateByXMatrix(rotX,ayy::DegToRad(_rotEuler.x()));
//    ayy::MakeRotateByYMatrix(rotY,ayy::DegToRad(_rotEuler.y()));
//    ayy::MakeRotateByZMatrix(rotZ,ayy::DegToRad(_rotEuler.z()));
//
//    _lookDir = (_lookDir * rotX * rotY * rotZ);
//
//    _lookDir.Normalize();
    
    _bViewMatDirty = true;
}

void Camera::SetLookTarget(const ayy::Vec3f& lookTarget)
{
    _center = lookTarget;
    _bViewMatDirty = true;
}

ayy::Mat4x4f& Camera::GetProjMatrix()
{
    float cotangent = 1.0f / tan(DegToRad(GetFov() * 0.5f));
    float aspect = (float)_viewportWidth / (float)_viewportHeight;
    
    _projMat.Identify();
    
    _projMat.Set(0,0,cotangent / aspect);
    _projMat.Set(1,1,cotangent);
    _projMat.Set(2,2,-1.f * (GetFar() + GetNear())/(GetFar() - GetNear()));
    _projMat.Set(3,2,-1 * (2 * GetNear() * GetFar())/(GetFar() - GetNear()) );
    _projMat.Set(2,3,-1.f);
    _projMat.Set(3,3,0);          // 这里 如果设置为 0 ， 会导致整个顶点 x mvp 之后，w 为 0. 所以这样是不是不对？
    
    return _projMat;
}

}
