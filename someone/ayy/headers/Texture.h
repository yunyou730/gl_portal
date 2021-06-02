#pragma once
#include <glad/glad.h>
#include <string>

namespace ayy {

typedef enum
{
    NONE,
    RGB,
    RGBA,
}
ETextureDataFormat;


struct RawTexture
{
    RawTexture(const std::string& filePath);
    ~RawTexture();
    
    bool IsValid() const { return data != nullptr;}
    
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
    ETextureDataFormat format = ETextureDataFormat::NONE;
    

};

class Texture
{
public:

    
    
public:
    Texture* CreateWithRawTexture(RawTexture* rawTexture);
    
protected:
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
    GLuint  _textureID = 0;
};

}

