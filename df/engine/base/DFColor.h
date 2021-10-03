#pragma once

namespace df {

struct Color3F
{
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
    
    Color3F() {}
    
    Color3F(float r,float g,float b)
        :r(r),g(g),b(b)
    {
        
    }
    
    Color3F(const Color3F& other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
    }
        
    void operator = (const Color3F& other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
    }
};

struct Color4F
{
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
    float a = 1.f;
    
    Color4F() {}
    
    Color4F(float r,float g,float b,float a)
        :r(r),g(g),b(b),a(a)
    {
        
    }
    
    Color4F(const Color4F& other) {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        this->a = other.a;
    }
    
    Color4F(const Color3F& other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        this->a = 1.0f;
    }
    
    void operator = (const Color4F& other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        this->a = other.a;
    }
};


}
