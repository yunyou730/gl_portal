#pragma once
#include <glad/glad.h>
#include <iostream>

namespace ayy {

/*
    基于 行向量,向量 x 矩阵 时，向量在左侧 的原则, 实现数学库
 */


//template<typename T>
//struct Vec3
//{
//    union
//    {
//        T data[3];
//
//        struct
//        {
//            T x,y,z;
//        };
//
//        struct
//        {
//            T r,g,b;
//        };
//    };
//};

template<typename T>
struct Vec4
{
    union
    {
        T data[4];
        
        struct
        {
            T x,y,z,w;
        };
        
        struct
        {
            T r,g,b,a;
        };

    };
    
    Vec4()
    {
        x = y = z = w = 0;
    }
    
    Vec4(T x,T y,T z,T w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    
    T operator[](int index)
    {
        return data[index];
    }
    
    
    Vec4<T> operator+(const Vec4<T>& other)
    {
        Vec4<T> ret(x + other.x,y + other.y,z + other.z,w + other.w);
        return ret;
    }
    
    Vec4<T> operator-(const Vec4<T>& other)
    {
        Vec4<T> ret(x - other.x,y - other.y,z - other.z,w - other.w);
        return ret;
    }
    
    
    void Dump()
    {
        printf("Vec4[%.3f,%.3f,%.3f]\n",x,y,z,w);
    }
};


typedef Vec4<float> Vec4f;


}

