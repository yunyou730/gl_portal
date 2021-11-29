#include "AYYQuaternion.h"

namespace ayy
{


 
Quaternion Quaternion::identity(0, 0, 0, 1);
 
 
Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    float mag = _x *_x + _y*_y + _z *_z + _w*_w;
    x = _x / mag;
    y = _y / mag;
    z = _z / mag;
    w = _w / mag;
}
 
Quaternion::Quaternion(float yaw, float pitch, float roll)
{
    this->SetEulerAngle(yaw, pitch, roll);
}
 
Quaternion::~Quaternion()
{
 
}
 
 
//Cos theta of two quaternion
float Quaternion::Dot(const Quaternion &lhs, const Quaternion &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
 
Quaternion Quaternion::Slerp(const Quaternion &a, const Quaternion &b, float t)
{
    float cos_theta = Dot(a, b);
 
    // if B is on opposite hemisphere from A, use -B instead
    float sign;
    if (cos_theta < 0.f)
    {
        cos_theta = -cos_theta;
        sign = -1.f;
    }
    else sign = 1.f;
 
    float c1, c2;
    if (cos_theta > 1.f - ayy::EPSILON)
    {
        // if q2 is (within precision limits) the same as q1,
        // just linear interpolate between A and B.
 
        c2 = t;
        c1 = 1.f - t;
    }
    else
    {
        //float theta = gFloat::ArcCosTable(cos_theta);
        // faster than table-based :
        //const float theta = myacos(cos_theta);
        float theta = acos(cos_theta);
        float sin_theta = sin(theta);
        float t_theta = t*theta;
        float inv_sin_theta = 1.f / sin_theta;
        c2 = sin(t_theta) * inv_sin_theta;
        c1 = sin(theta - t_theta) * inv_sin_theta;
    }
 
    c2 *= sign; // or c1 *= sign
                // just affects the overrall sign of the output
 
                // interpolate
    return Quaternion(a.x * c1 + b.x * c2, a.y * c1 + b.y * c2, a.z * c1 + b.z * c2, a.w * c1 + b.w * c2);
}
 
Quaternion Quaternion::Lerp(const Quaternion &a, const Quaternion &b, float t)
{
    return Quaternion((1 - t) * a.x + t * b.x,
        (1 - t) * a.y + t * b.y,
        (1 - t) * a.z + t * b.z,
        (1 - t) * a.w + t * b.w);
}
 
float Quaternion::Angle(const Quaternion &lhs, const Quaternion &rhs)
{
    float cos_theta = Dot(lhs, rhs);
 
    // if B is on opposite hemisphere from A, use -B instead
    if (cos_theta < 0.f)
    {
        cos_theta = -cos_theta;
    }
    float theta = acos(cos_theta);
//    return 2 * Mathf::Rad2Deg * theta;
    return 2 * ayy::RadToDeg(theta);
}
 
 
void Quaternion::Set(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}
 
void Quaternion::SetEulerAngle(float yaw, float pitch, float roll)
{
    float  angle;
    float  sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;
 
    angle = yaw * 0.5f;
    sinYaw = sin(angle);
    cosYaw = cos(angle);
 
    angle = pitch * 0.5f;
    sinPitch = sin(angle);
    cosPitch = cos(angle);
 
    angle = roll * 0.5f;
    sinRoll = sin(angle);
    cosRoll = cos(angle);
 
    float _y = cosRoll*sinPitch*cosYaw + sinRoll*cosPitch*sinYaw;
    float _x = cosRoll*cosPitch*sinYaw - sinRoll*sinPitch*cosYaw;
    float _z = sinRoll*cosPitch*cosYaw - cosRoll*sinPitch*sinYaw;
    float _w = cosRoll*cosPitch*cosYaw + sinRoll*sinPitch*sinYaw;
 
    float mag = _x *_x + _y*_y + _z *_z + _w*_w;
    x = _x / mag;
    y = _y / mag;
    z = _z / mag;
    w = _w / mag;
}
 
 
void Quaternion::operator+(const Quaternion &q)
{
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
}
 
void Quaternion::operator-(const Quaternion &q)
{
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
}
 
void Quaternion::operator*(float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;
}
 
Quaternion Quaternion::Conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}
 
Quaternion Quaternion::Inverse() const
{
    return Quaternion(-x, -y, -z, w);
}
 
Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs)
{
    float w1 = lhs.w;
    float w2 = rhs.w;
    ayy::Vec3f v1(lhs.x, lhs.y, lhs.z);
    ayy::Vec3f v2(rhs.x, rhs.y, rhs.z);
    float w3 = w1 * w2 - v1.Dot(v2);//ayy::Dot(v1, v2);
//    ayy::Vec3f v3 = ayy::Cross(v1, v2) + w1 * v2 + w2 * v1;
    ayy::Vec3f v3 = v1.Cross(v2) + w1 * v2 + w2 * v1;
    return Quaternion(v3.x(), v3.y(), v3.z(), w3);
}
 
ayy::Vec3f operator *(const Quaternion& q, const ayy::Vec3f& v)
{
 
/*
    Quaternion tmp(v.x, v.y, v.z, 0); //This will normalise the quaternion. this will case error.
    Quaternion result = q * tmp * q.Conjugate();
    return Vector3(result.x, result.y, result.z);*/
 
    // Extract the vector part of the quaternion
    ayy::Vec3f u(q.x, q.y, q.z);
 
    // Extract the scalar part of the quaternion
    float s = q.w;
 
    // Do the math
//    return 2.0f * Vector3::Dot(u, v) * u
//        + (s*s - Vector3::Dot(u, u)) * v
//        + 2.0f * s * Vector3::Cross(u, v);
    
    return 2.0f * u.Dot(v) * u
        + (s*s - u.Dot(u)) * v
        + 2.0f * s * u.Cross(v);
    
}
 
ayy::Vec3f Quaternion::EulerAngle() const
{
    float yaw = atan2(2 * (w * x + z * y), 1 - 2 * (x * x + y * y));
    
    float temp = 2 * (w * y - x * z);
    ayy::Clamp<float>(temp, -1.0f, 1.0f);
    float pitch = asin(temp);
    
    float roll = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y));
//    return Vector3(Mathf::Rad2Deg * yaw, Mathf::Rad2Deg * pitch, Mathf::Rad2Deg * roll);
    return ayy::Vec3f(ayy::RadToDeg(yaw) , ayy::RadToDeg(pitch), ayy::RadToDeg(roll));
}
 
}
 
