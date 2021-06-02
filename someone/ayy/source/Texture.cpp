#include "../headers/Texture.h"
#include "stb_image.h"

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
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_textureID);
    
    
    GLuint saveFormat = 0;
    GLuint rawFormat = 0;

    switch(rawTexture->format)
    {
        case ETextureDataFormat::RGB:
            saveFormat = GL_RGB;
            rawFormat = GL_RGB;
            break;
        case ETextureDataFormat::RGBA:
            saveFormat = GL_RGBA;
            rawFormat = GL_RGBA;
            break;
    }

    glTexImage2D(GL_TEXTURE_2D,0,
                 saveFormat,
                 rawTexture->width,
                 rawTexture->height,
                 0,
                 rawFormat,
                 GL_UNSIGNED_BYTE,
                 rawTexture->data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
}

Texture::~Texture()
{
    glDeleteTextures(1,&_textureID);
    _textureID = 0;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D,_textureID);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

}
