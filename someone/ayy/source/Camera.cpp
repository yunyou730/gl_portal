#include "Camera.h"

namespace ayy {
Camera::Camera()
{
    _pos.SetX(0);_pos.SetY(0);_pos.SetZ(0);
    _euler.SetX(0);_euler.SetY(0);_euler.SetZ(0);
//    _lookDir.SetX(0);_lookDir.SetY(0);_lookDir.SetZ(-1);
    _viewMat.Identify();
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

}
