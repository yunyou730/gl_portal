#include "Math.h"

namespace ayy
{

float RadToDeg(float rad)
{
    return rad / PI * 180.f;
}

float DegToRad(float deg)
{
    return deg / 180 * PI;
}

void MakeScaleMatrix(Mat4x4f& mat,float scale)
{
    mat.Identify();
    mat.data[0][0] = scale;
    mat.data[1][1] = scale;
    mat.data[2][2] = scale;
}

void MakeScaleMatrix(Mat4x4f& mat,float sx,float sy,float sz)
{
    mat.Identify();
    mat.data[0][0] = sx;
    mat.data[1][1] = sy;
    mat.data[2][2] = sz;
}

void MakeTranslateMatrix(Mat4x4f& mat,float ox,float oy,float oz)
{
    mat.Identify();
    mat.data[3][0] = ox;
    mat.data[3][1] = oy;
    mat.data[3][2] = oz;
}

void MakeRotateByXMatrix(Mat4x4f& mat,float rad)
{
    float sinValue = sin(rad);
    float cosValue = cos(rad);
 
    mat.Identify();
    mat.data[1][1] = cosValue;
    mat.data[2][2] = cosValue;
    mat.data[1][2] = sinValue;
    mat.data[2][1] = -sinValue;
}

void MakeRotateByYMatrix(Mat4x4f& mat,float rad)
{
    float sinValue = sin(rad);
    float cosValue = cos(rad);
    
    mat.Identify();
    mat.data[0][0] = cosValue;
    mat.data[2][2] = cosValue;
    mat.data[2][0] = sinValue;
    mat.data[0][2] = -sinValue;
    
}

void MakeRotateByZMatrix(Mat4x4f& mat,float rad)
{
    float sinValue = sin(rad);
    float cosValue = cos(rad);
    
    mat.Identify();
    mat.data[0][0] = cosValue;
    mat.data[1][1] = cosValue;
    mat.data[1][0] = -sinValue;
    mat.data[0][1] = sinValue;
}


void MakeRotateByAxisMatrix(Mat4x4f& mat,const Vec3f& axis,float rad)
{
    float sinV = sin(rad);
    float cosV = cos(rad);
    
    Vec3f axisDir = axis.GetNormalize();
    float nx = axisDir.x();
    float ny = axisDir.y();
    float nz = axisDir.z();
    
    mat.Identify();

    /*
    mat.data[0][0] = nx * nx * (1 - cosV) + cosV;
    mat.data[1][0] = nx * ny * (1 - cosV) + nz * cosV;
    mat.data[2][0] = nx * nz * (1 - cosV) - ny * sinV;
    
    mat.data[0][1] = nx * ny * (1 - cosV) - nz * sinV;
    mat.data[1][1] = ny * ny * (1 - cosV) + cosV;
    mat.data[2][1] = ny * nz * (1 - cosV) + nx * sinV;
    
    mat.data[0][2] = nx * nz * (1 - cosV) + ny * sinV;
    mat.data[1][2] = ny * nz * (1 - cosV) - nx * sinV;
    mat.data[2][2] = nz * nz * (1 - cosV) + cosV;
    */
    
    mat.data[0][0] = nx * nx * (1 - cosV) + cosV;
    mat.data[0][1] = nx * ny * (1 - cosV) + nz * sinV;
    mat.data[0][2] = nx * nz * (1 - cosV) - ny * sinV;
    
    mat.data[1][0] = nx * ny * (1 - cosV) - nz * sinV;
    mat.data[1][1] = ny * ny * (1 - cosV) + cosV;
    mat.data[1][2] = ny * nz * (1 - cosV) + nx * sinV;
    
    mat.data[2][0] = nx * nz * (1 - cosV) + ny * sinV;
    mat.data[2][1] = ny * nz * (1 - cosV) - nx * sinV;
    mat.data[2][2] = nz * nz * (1 - cosV) + cosV;
}

}
