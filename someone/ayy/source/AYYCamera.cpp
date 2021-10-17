#include "../headers/AYYCamera.h"

namespace ayy
{

/*
    default pos  (0,0,5)
    default look dir (0,0,-1,0) // w = 0 means vector is a direction
 
    right hand coordinate
 */
const static ayy::Vec3f kWorldUpDir(0,1,0);
const static ayy::Vec3f kDefaultPos(0,0,-5);
const static ayy::Vec3f kDefaultLookDir(0,0,1);

Camera::Camera(int viewportWidth,int viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
    ,_fov(45)
    ,_far(100.0f)
    ,_near(0.1f)
//    ,_near(3.0f)
    ,_mode(ECamProjMode::PROJECTION)
{
    _eye = kDefaultPos;
    SetLookDir(kDefaultLookDir);
    
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
    
    z = _lookDir * -1;
    x = _rightDir;
    y = _upDir;
    
    ayy::Mat4x4f matRot,matTrans;
    
    matRot.Identify();
    
    matRot.Set(0,0,x.x());    matRot.Set(1,0,x.y());    matRot.Set(2,0,x.z());
    matRot.Set(0,1,y.x());    matRot.Set(1,1,y.y());    matRot.Set(2,1,y.z());
    matRot.Set(0,2,z.x());    matRot.Set(1,2,z.y());    matRot.Set(2,2,z.z());
    
    matTrans.Identify();
    matTrans.Set(3,0,-_eye.Dot(x));
    matTrans.Set(3,1,-_eye.Dot(y));
    matTrans.Set(3,2,-_eye.Dot(z));
    
    _viewMat = matRot * matTrans;
}

void Camera::TakeMove(float deltaX,float deltaY,float deltaZ)
{
    _eye.SetX(_eye.x() + deltaX);
    _eye.SetY(_eye.y() + deltaY);
    _eye.SetZ(_eye.z() + deltaZ);
    _bViewMatDirty = true;
}

// rot by local x
void Camera::TakePitch(float deltaDeg)
{
    _pitch += deltaDeg;
    ayy::Clamp<float>(_pitch,-90,90);
    CalcLocalAxis();
    _bViewMatDirty = true;
}

// rot by local y
void Camera::TakeYaw(float deltaDeg)
{
    _yaw += deltaDeg;
    CalcLocalAxis();
    _bViewMatDirty = true;
}

// rot by local z
void Camera::TakeRoll(float deltaDeg)
{
    _roll += deltaDeg;
    CalcLocalAxis();
    _bViewMatDirty = true;
}

ayy::Mat4x4f& Camera::GetProjMatrix()
{
    if(_bProjMatDirty)
    {
        switch(_mode)
        {
            case ECamProjMode::PROJECTION:
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
                break;
            case ECamProjMode::ORTHO:
            {
                _projMat.Identify();
                _projMat.Set(0,0,2.0 / (_orthoRight - _orthoLeft));
                _projMat.Set(1,1,2.0 / (_orthoTop - _orthoBottom));
                _projMat.Set(2,2,-2.0 / (_far - _near));
                
                _projMat.Set(3,0,-1.0 * (_orthoRight + _orthoLeft) / (_orthoRight - _orthoLeft));
                _projMat.Set(3,1,-1.0 * (_orthoTop + _orthoBottom) / (_orthoTop - _orthoBottom));
                _projMat.Set(3,2,-1.0 * (_far + _near) / (_far - _near));
                
            }
                break;
            default:
                break;
        }

    }
    return _projMat;
}

// @miao @test
static void CalcRightUpByLook(const ayy::Vec3f lookDir,ayy::Vec3f& rightDir,ayy::Vec3f& upDir)
{
    rightDir = kWorldUpDir.Cross(lookDir).Normalize();
    upDir = lookDir.Cross(rightDir).Normalize();
}

void Camera::CalcLocalDirByLookDir()
{
    CalcRightUpByLook(_lookDir,_rightDir,_upDir);
}

void Camera::CalcLocalAxis()
{
    // base look dir
    ayy::Vec4f baseLookDir;
    baseLookDir.SetX(_baseLookDir.x());
    baseLookDir.SetY(_baseLookDir.y());
    baseLookDir.SetZ(_baseLookDir.z());
    baseLookDir.SetW(0.0f);
    
    // rot matrix
    ayy::Mat4x4f rotX,rotY,rotZ;
    
//    ayy::MakeRotateByAxisMatrix(rotY,ayy::Vec3f(0,1,0),ayy::DegToRad(_yaw));
//    ayy::MakeRotateByAxisMatrix(rotX,ayy::Vec3f(1,0,0),ayy::DegToRad(_pitch));
//    ayy::MakeRotateByAxisMatrix(rotZ,ayy::Vec3f(0,0,1),ayy::DegToRad(_roll));
    
    ayy::MakeRotateByYMatrix(rotY,ayy::DegToRad(_yaw));
    ayy::MakeRotateByAxisMatrix(rotX, _baseRightDir, ayy::DegToRad(_pitch));
    
    // look dir
    ayy::Vec4f tempLookDir = baseLookDir * rotX * rotY;// * rotZ;
    tempLookDir.Normalize();
    tempLookDir = tempLookDir;
    
    _lookDir.SetX(tempLookDir.x());
    _lookDir.SetY(tempLookDir.y());
    _lookDir.SetZ(tempLookDir.z());
    _lookDir.Normalize();
    
    CalcLocalDirByLookDir();
}


void Camera::SetPos(const ayy::Vec3f& pos)
{
    _eye = pos;
}

void Camera::SetLookDir(const ayy::Vec3f& lookDir)
{
    _baseLookDir = lookDir;
    _baseLookDir.Normalize();
    
    CalcRightUpByLook(_baseLookDir,_baseRightDir,_baseUpDir);
    
    _lookDir = _baseLookDir;
    
    _pitch = _yaw = _roll = 0.0;
    
    CalcLocalDirByLookDir();
    _bViewMatDirty = true;
}

void Camera::Dump() const
{
    // dump
    printf("----------- camera dump begin -----------\n");
    
    printf("camera pos");
    GetPos().Dump();
    
    ayy::Vec3f look = GetLookDir();
    printf("camera look");
    look.Dump();


    ayy::Vec3f localXDir = GetRightDir();
    printf("localXDir");
    localXDir.Dump();

    ayy::Vec3f up = GetUpDir();

    float dot = localXDir.Dot(look);
    printf("left dot look:%.5f\n",dot);

    dot = up.Dot(look);
    printf("up dot look:%.5f\n",dot);

    dot = up.Dot(localXDir);
    printf("up dot left:%.5f\n",dot);
    
    printf("----------- camera dump end -----------\n");
}
}
