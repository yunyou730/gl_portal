#pragma once
#include <glad/glad.h>
#include <string>
#include "RawTexture.h"

namespace ayy {


typedef unsigned int TextureUUID;

typedef enum TextureType
{
    TT_None,
    
    TT_2D,
    TT_RT,
};

class Texture
{
public:
    Texture(TextureUUID uuid,int width,int height);
    Texture(TextureUUID uuid,RawTexture* rawTexture);
    ~Texture();
    
    void Bind(GLuint textureIndex);
    void UnBind();
    
    unsigned int GetUUID() const { return _uuid;}
    GLuint GetGLTextureID() { return _textureID;}
    
protected:
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
    GLuint  _textureID = 0;
    
    RawTexture* _raw = nullptr;
    GLuint _saveFormat = 0;
    GLuint _rawFormat = 0;
    
    TextureUUID _uuid = 0;
    
    TextureType     _type = TextureType::TT_None;
};

}

