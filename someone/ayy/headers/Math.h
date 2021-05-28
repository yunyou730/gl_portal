#pragma once
#include <glad/glad.h>
#include <iostream>

namespace ayy {


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
};

typedef Vec4<float> Vec4f;


}

