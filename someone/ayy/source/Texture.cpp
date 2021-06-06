#include "../headers/Texture.h"
#include "stb_image.h"
#include <cassert>

namespace ayy {
Texture* Texture::CreateWithRawTexture(RawTexture* rawTexture)
{
    if(!rawTexture->IsValid())
    {
        return nullptr;
    }
    
    Texture* tex = new Texture(rawTexture);
    return tex;
}

Texture::Texture(RawTexture* rawTexture)
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

}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

}
