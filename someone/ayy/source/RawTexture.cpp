#include "../headers/AYYTexture.h"
#include "stb_image.h"

namespace ayy {

RawTexture::RawTexture()
{
    
}

RawTexture::RawTexture(const std::string& filePath)
{
    data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    switch(channels)
    {
        case 3:
            format = ETextureDataFormat::RGB;
            break;
        case 4:
            format = ETextureDataFormat::RGBA;
            break;
        default:
            // warning!
            format = ETextureDataFormat::NONE;
            break;
    }
}

RawTexture::RawTexture(RawTexture&& other)
{
    this->width = other.width;
    this->height = other.height;
    this->channels = other.channels;
    this->format = other.format;
    this->data = other.data;
    other.data = nullptr;
}

RawTexture::~RawTexture()
{
    if(data != nullptr)
    {
        stbi_image_free(data);
        data = nullptr;
    }
    format = ETextureDataFormat::NONE;
}

}
