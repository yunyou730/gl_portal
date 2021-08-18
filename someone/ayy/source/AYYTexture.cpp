#include "../headers/AYYTexture.h"
#include "stb_image.h"
#include <cassert>
#include <vector>
#include <string>
#include "Ayy.h"

namespace ayy {

Texture2D::Texture2D(TextureUUID uuid,int width,int height)
    :BaseTexture(uuid,TextureType::TT_RT)
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
    
    _saveFormat = GL_RGB;
    _rawFormat = GL_RGB;    // useless
}

Texture2D::Texture2D(TextureUUID uuid,RawTexture* rawTexture)
    :BaseTexture(uuid,TextureType::TT_2D)
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

Texture2D::~Texture2D()
{
    glDeleteTextures(1,&_textureID);
    _textureID = 0;
    
    if(_raw != nullptr)
    {
        delete _raw;
    }
    _raw = nullptr;
}

void Texture2D::Bind(GLuint textureIndex)
{
    switch(_type)
    {
        case TextureType::TT_2D:
            glActiveTexture(textureIndex);
            glBindTexture(GL_TEXTURE_2D,_textureID);
            
            
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //字节对齐
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

void Texture2D::UnBind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}


// -----------

TextureCube::TextureCube(TextureUUID uuid,
                            const std::string& right,
                            const std::string& left,
                            const std::string& top,
                            const std::string& bottom,
                            const std::string& back,
                            const std::string& front)
    :BaseTexture(uuid,TextureType::TT_CUBE)
{
    glGenTextures(1,&_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
    /*
     GL_TEXTURE_CUBE_MAP_POSITIVE_X    右
     GL_TEXTURE_CUBE_MAP_NEGATIVE_X    左
     GL_TEXTURE_CUBE_MAP_POSITIVE_Y    上
     GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    下
     GL_TEXTURE_CUBE_MAP_POSITIVE_Z    后
     GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    前
     **/
    
    std::vector<std::string> texturePath;
    texturePath.push_back(right);
    texturePath.push_back(left);
    texturePath.push_back(top);
    texturePath.push_back(bottom);
//    texturePath.push_back(back);
    texturePath.push_back(front);       // 这里要注意顺序 !!
    texturePath.push_back(back);
    
    int width,height,nrChannels;
    unsigned char* data = nullptr;
    for(unsigned int i = 0;i < texturePath.size();i++)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //字节对齐
        
        data = stbi_load(texturePath[i].c_str(), &width, &height, &nrChannels, 0);
        assert(data != nullptr);
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        stbi_image_free(data);
        data = nullptr;
    }
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureCube::~TextureCube()
{
    glDeleteTextures(1,&_textureID);
    _textureID = 0;
}

void TextureCube::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
    glCheckError();
}

void TextureCube::UnBind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

}
