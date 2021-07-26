#include "../headers/Texture.h"
#include "stb_image.h"
#include <cassert>

namespace ayy {


Texture::Texture(TextureUUID uuid,int width,int height)
    :_uuid(uuid)
    ,_type(TextureType::TT_RT)
{
    glGenTextures(1,&_textureID);
    glBindTexture(GL_TEXTURE_2D,_textureID);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 nullptr);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    _saveFormat = GL_RGB;
    _rawFormat = GL_RGB;    // useless
}

Texture::Texture(TextureUUID uuid,RawTexture* rawTexture)
    :_uuid(uuid)
    ,_type(TextureType::TT_2D)
{
    glGenTextures(1,&_textureID);
    
    _raw = new RawTexture(std::move(*rawTexture));
    
    switch(_raw->format)
    {
        case ETextureDataFormat::RGB:
            _saveFormat = GL_RGB;
            _rawFormat = GL_RGB;
            break;
        case ETextureDataFormat::RGBA:
            _saveFormat = GL_RGBA;
            _rawFormat = GL_RGBA;
            break;
        default:
            assert(false); // invalid RawTextureFormat
            break;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1,&_textureID);
    _textureID = 0;
    
    if(_raw != nullptr)
    {
        delete _raw;
    }
    _raw = nullptr;
    
}

void Texture::Bind(GLuint textureIndex)
{
    
    switch(_type)
    {
        case TextureType::TT_2D:
            glActiveTexture(textureIndex);
            glBindTexture(GL_TEXTURE_2D,_textureID);
            
            // Pass data from memory to GPU
            glTexImage2D(GL_TEXTURE_2D,0,
                         _saveFormat,
                         _raw->width,
                         _raw->height,
                         0,
                         _rawFormat,
                         GL_UNSIGNED_BYTE,
                         _raw->data);
            
            glGenerateMipmap(GL_TEXTURE_2D);
            break;
        case TextureType::TT_RT:
            glActiveTexture(textureIndex);
            glBindTexture(GL_TEXTURE_2D,_textureID);
            break;
        default:
            break;
    }
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

}
