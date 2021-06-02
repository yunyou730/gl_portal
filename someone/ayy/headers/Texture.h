#pragma once
#include <glad/glad.h>
#include <string>
#include "RawTexture.h"

namespace ayy {

class Texture
{
public:

public:
    static Texture* CreateWithRawTexture(RawTexture* rawTexture);
    
    Texture(RawTexture* rawTexture);
    ~Texture();
    
    void Bind();
    void UnBind();
protected:
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
    GLuint  _textureID = 0;
};

}

