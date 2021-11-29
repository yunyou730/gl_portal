#pragma once
#include "AYYMath.h"

namespace ayy {

class Quaternion
{
public:
    Quaternion(float x, float y, float z, float w);
    Quaternion(float yaw, float pitch, float roll);
    ~Quaternion();
    static Quaternion identity;
    static float Dot(const Quaternion &lhs, const Quaternion &rhs);
    static Quaternion Lerp(const Quaternion &a, const Quaternion &b, float t);
    static Quaternion Slerp(const Quaternion &a, const Quaternion &b, float t);
    static float Angle(const Quaternion &lhs, const Quaternion &rhs);
    void SetEulerAngle(float yaw, float pitch, float roll);
    void Set(float _x, float _y, float _z, float _w);
 
    Quaternion Conjugate() const;
    Quaternion Inverse() const;
    ayy::Vec3f EulerAngle() const;
 
    void operator+(const Quaternion &q);
    void operator*(float s);
    void operator-(const Quaternion &q);
    friend Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
    friend ayy::Vec3f operator *(const Quaternion& rotation, const ayy::Vec3f& point);
 
    float x;
    float y;
    float z;
    float w;
 
private:
    
    ayy::Vec3f eulerAngles;
};
}
