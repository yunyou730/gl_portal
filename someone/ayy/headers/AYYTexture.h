#pragma once
#include <glad/glad.h>
#include <string>
#include "AYYRawTexture.h"

namespace ayy {


typedef unsigned int TextureUUID;

typedef enum
{
    TT_None,
    
    TT_2D,
    TT_RT,
    TT_CUBE,
} TextureType;

class BaseTexture
{
public:
    BaseTexture(TextureUUID uuid,TextureType textureType)
        :_uuid(uuid)
        ,_type(textureType)
    {}
    virtual ~BaseTexture() {}
    
    virtual void Bind(GLuint textureIndex) = 0;
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    
    GLuint GetGLTextureID() { return _textureID;}
    unsigned int GetUUID() const { return _uuid;}
    
protected:
    GLuint  _textureID = 0;
    TextureType _type = TextureType::TT_None;
    TextureUUID _uuid = 0;
};

class Texture2D : public BaseTexture
{
public:
    Texture2D(TextureUUID uuid,int width,int height);
    Texture2D(TextureUUID uuid,RawTexture* rawTexture);
    virtual ~Texture2D();
    
    void Bind() override { assert(false);}
    void Bind(GLuint textureIndex) override;
    void UnBind() override;
    
protected:
    RawTexture* _raw = nullptr;
    GLuint _saveFormat = 0;
    GLuint _rawFormat = 0;
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
};

class TextureCube : public BaseTexture
{
public:
    TextureCube(TextureUUID uuid,
                const std::string& right,
                const std::string& left,
                const std::string& top,
                const std::string& bottom,
                const std::string& back,
                const std::string& front);
    
    virtual ~TextureCube();
    
    virtual void Bind() override;
    void Bind(GLuint textureIndex) override { assert(false);}
    virtual void UnBind() override;
};


}

