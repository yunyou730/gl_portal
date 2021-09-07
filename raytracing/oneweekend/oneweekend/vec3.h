#pragma once

#include <cmath>
#include <iostream>

template<class T>
class vec3
{
public:
    vec3():e{0,0,0} {}
    vec3(T e0,T e1,T e2):e{e0,e1,e2}{}
    
    T x() const {return e[0];}
    T y() const {return e[1];}
    T z() const {return e[2];}
    
    vec3 operator-() const {return vec3(-e[0],-e[1],-e[2]);}
    T operator[](int i) const {return e[i];}
    T& operator[](int i) {return e[i];}
    
    vec3& operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    
    vec3& operator*=(const T t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    
    vec3& operator/=(const T t)
    {
        *this *= 1.0/t;
        return *this;
    }
    
    T length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    
    T length() const
    {
        return sqrt(length_squared());
    }

public:
    T e[3];
};

using point3 = vec3<double>;
using color = vec3<double>;
