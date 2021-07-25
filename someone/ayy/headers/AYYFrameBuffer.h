#pragma once
#include <glad/glad.h>
#include <iostream>
#include "Math.h"

namespace ayy {

class AYYFrameBuffer
{
public:
    AYYFrameBuffer();
    ~AYYFrameBuffer();
    
    void Bind();
    void UnBind();
protected:
    void Gen();
    void Destroy();
    
protected:
    unsigned int _fbo = 0;
    unsigned int _texColoBuffer = 0;
    unsigned int _rbo = 0;
};

}

