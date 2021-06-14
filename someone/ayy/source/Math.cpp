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

void MakeTranslateMatrix(Mat4x4f& mat,float ox,float oy,float oz)
{
    mat.Identify();
    mat.data[0][3] = ox;
    mat.data[1][3] = oy;
    mat.data[2][3] = oz;
}

void MakeRotateByXMatrix(Mat4x4f& mat,float rad)
{
    mat.Identify();
    float sinValue = sin(rad);
    float cosValue = cos(rad);
    
    mat.data[1][1] = cosValue;
    mat.data[2][2] = cosValue;
    mat.data[1][2] = -sinValue;
    mat.data[2][1] = sinValue;
}

void MakeRotateByYMatrix(Mat4x4f& mat,float rad)
{
    float sinValue = sin(rad);
    float cosValue = cos(rad);
    
    mat.data[0][0] = cosValue;
    mat.data[2][2] = cosValue;
    mat.data[0][2] = sinValue;
    mat.data[2][0] = -sinValue;
    
}

void MakeRotateByZMatrix(Mat4x4f& mat,float rad)
{
    float sinValue = sin(rad);
    float cosValue = cos(rad);
    
    mat.data[0][0] = cosValue;
    mat.data[1][1] = cosValue;
    mat.data[0][1] = -sinValue;
    mat.data[1][0] = sinValue;
}
}
