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
    
    void Bind(GLuint textureIndex);
    void UnBind();
protected:
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
    GLuint  _textureID = 0;
    
    RawTexture* _raw = nullptr;
    GLuint _saveFormat = 0;
    GLuint _rawFormat = 0;
    
//    GLuint  _curTextureIdx = 0;
};

}

