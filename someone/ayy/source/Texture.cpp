#include "../headers/Texture.h"
#include "stb_image.h"

namespace ayy {

RawTexture::RawTexture(const std::string& filePath)
{
    data = stbi_load("res/container.jpg", &width, &height, &channels, 0);
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
