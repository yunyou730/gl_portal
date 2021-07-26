#pragma once
#include <glad/glad.h>
#include <string>
#include <map>
#include "Texture.h"

namespace ayy {


class TextureManager
{
    typedef std::map<TextureUUID,Texture*> TextureMap;
    typedef std::map<unsigned int,TextureUUID> TextureSlotMap;
    
    typedef std::map<std::string,TextureUUID> TexturePathMap;
    
public:
    static const TextureUUID kInvalidTextureUUID = 0;
    
public:
    static TextureManager* GetInstance();
    ~TextureManager();
    
    TextureUUID CreateTextureWithFilePath(const std::string& filePath);
    TextureUUID CreateTextureWithRaw(RawTexture* raw);
    TextureUUID CreateRenderTexture(int width,int height);
    
    Texture* GetTextureWithUUID(TextureUUID uuid);
    
    void BindTextureToSlot(TextureUUID texUUID,unsigned int slotIndex);
    
protected:
    TextureManager();
    TextureUUID NextUUID();
    
    void ClearTextureMap();
    void ClearTextureSlotMap();
    
protected:
    TextureUUID _uuidCounter = 0;
    
    TextureMap      _textureMap;
    TextureSlotMap  _textureSlotMap;
    
    // @miao @todo
    TexturePathMap  _texturePathMap;
    
};

}

