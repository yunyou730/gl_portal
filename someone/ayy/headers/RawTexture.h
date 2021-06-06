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
    RawTexture();
    RawTexture(const std::string& filePath);
    ~RawTexture();
    
    RawTexture(RawTexture&& other);
    
    bool IsValid() const { return data != nullptr;}
    
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
    ETextureDataFormat format = ETextureDataFormat::NONE;
};
}

