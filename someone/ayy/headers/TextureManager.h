#pragma once
#include <glad/glad.h>
#include <string>
#include <map>
#include "AYYTexture.h"

namespace ayy {


class TextureManager
{
    typedef std::map<TextureUUID,ayy::BaseTexture*> TextureMap;
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
    TextureUUID CreateCubeTexture(const std::string& right,
                                  const std::string& left,
                                  const std::string& top,
                                  const std::string& bottom,
                                  const std::string& back,
                                  const std::string& front);
    
    ayy::BaseTexture* GetTextureWithUUID(TextureUUID uuid);
    
    void BindTextureToSlot(TextureUUID texUUID,unsigned int slotIndex);
    void BindTextureToCube(TextureUUID texUUID);
    void UnBindCubeTexture(TextureUUID texUUID);
    
protected:
    TextureManager();
    TextureUUID NextUUID();
    
    void ClearTextureMap();
    void ClearTextureSlotMap();
    
protected:
    TextureUUID _uuidCounter = 0;
    
    TextureMap      _textureMap;
    TextureSlotMap  _textureSlotMap;
    
    TexturePathMap  _texturePathMap;
    
};

}

