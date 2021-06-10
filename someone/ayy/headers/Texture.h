#pragma once
#include <glad/glad.h>
#include <string>
#include "RawTexture.h"

namespace ayy {


typedef unsigned int TextureUUID;
class Texture
{
public:    
    Texture(TextureUUID uuid,RawTexture* rawTexture);
    ~Texture();
    
    void Bind(GLuint textureIndex);
    void UnBind();
    
    unsigned int GetUUID() const { return _uuid;}
    
protected:
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
    GLuint  _textureID = 0;
    
    RawTexture* _raw = nullptr;
    GLuint _saveFormat = 0;
    GLuint _rawFormat = 0;
    
    TextureUUID _uuid = 0;
};

}

