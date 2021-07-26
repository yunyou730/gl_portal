#pragma once
#include <glad/glad.h>
#include <iostream>
#include "Math.h"

#include "TextureManager.h"

namespace ayy {

class AYYFrameBuffer
{
public:
    AYYFrameBuffer(int width,int height);
    ~AYYFrameBuffer();
    
    void Bind();
    void UnBind();
    
    GLuint GetGLTextureID();
    TextureUUID GetTextureUUID();
    
protected:
    void Gen();
    void Destroy();
    
protected:
    unsigned int _fbo = 0;
    unsigned int _texColoBuffer = 0;
    unsigned int _rbo = 0;
    
    TextureUUID _rtUUID = TextureManager::kInvalidTextureUUID;
    
    int _width;
    int _height;
};

}
