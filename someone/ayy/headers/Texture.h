#pragma once


namespace ayy {



class Texture
{
public:
    struct RawTexture
    {
        int width = 0;
        int height = 0;
        int channels = 0;
        unsigned char* data = nullptr;
    };
    
    typedef enum
    {
        NONE,
        RGB,
        RGBA,
    }
    ETextureDataFormat;
    
public:

    
protected:
    ETextureDataFormat  _format = ETextureDataFormat::NONE;
    
};

}

