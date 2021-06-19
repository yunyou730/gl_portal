#include "Camera.h"

namespace ayy {
Camera::Camera(int viewportWidth,int viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
    ,_fov(45)
    ,_far(10.0f)
    ,_near(0.1f)
{
    _pos.SetX(0);_pos.SetY(0);_pos.SetZ(5.0f);
    _euler.SetX(0);_euler.SetY(0);_euler.SetZ(0);
//    _lookDir.SetX(0);_lookDir.SetY(0);_lookDir.SetZ(-1);
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
    Mat4x4f invertTranslate;
    Mat4x4f invertRotByX,invertRotByY,invertRotByZ;
    
    MakeTranslateMatrix(invertTranslate,-_pos.x(),-_pos.y(),-_pos.z());
    MakeRotateByXMatrix(invertRotByX,DegToRad(-_euler.x()));
    MakeRotateByXMatrix(invertRotByY,DegToRad(-_euler.y()));
    MakeRotateByXMatrix(invertRotByZ,DegToRad(-_euler.z()));
    
    _viewMat = invertRotByX * invertRotByY * invertRotByZ * invertTranslate;
}

void Camera::TakeMove(float deltaX,float deltaY,float deltaZ)
{
    _pos.SetX(_pos.x() + deltaX);
    _pos.SetY(_pos.y() + deltaY);
    _pos.SetZ(_pos.z() + deltaZ);
    _bViewMatDirty = true;
}

void Camera::TakeRot(float deltaDegX,float deltaDegY,float deltaDegZ)
{
    _euler.SetX(_euler.x() + deltaDegX);
    _euler.SetY(_euler.y() + deltaDegY);
    _euler.SetZ(_euler.z() + deltaDegZ);
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
