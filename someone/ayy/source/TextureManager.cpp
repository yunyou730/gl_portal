#include "TextureManager.h"

namespace ayy {

TextureManager* TextureManager::GetInstance()
{
    static TextureManager instance;
    return &instance;
}

TextureManager::TextureManager()
{
    
}

TextureManager::~TextureManager()
{
    ClearTextureMap();
    ClearTextureSlotMap();
}

TextureUUID TextureManager::CreateTextureWithFilePath(const std::string& filePath)
{
    RawTexture raw(filePath);
    TextureUUID uuid = CreateTextureWithRaw(&raw);
    return uuid;
}

TextureUUID TextureManager::CreateTextureWithRaw(RawTexture* raw)
{
    if(!raw->IsValid())
    {
        return 0;
    }
    
    TextureUUID uuid = NextUUID();
    Texture* tex = new Texture(uuid,raw);
    
    _textureMap.insert(std::make_pair(uuid,tex));
    
    return uuid;
}

TextureUUID TextureManager::NextUUID()
{
    _uuidCounter++;
    return _uuidCounter;
}

void TextureManager::ClearTextureMap()
{
    for(TextureMap::iterator it = _textureMap.begin();it != _textureMap.end();it++)
    {
        delete it->second;
    }
    _textureMap.clear();
}

void TextureManager::ClearTextureSlotMap()
{
    _textureSlotMap.clear();
}

Texture* TextureManager::GetTextureWithUUID(TextureUUID uuid)
{
    TextureMap::iterator it = _textureMap.find(uuid);
    if(it != _textureMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void TextureManager::BindTextureToSlot(TextureUUID texUUID,unsigned int slotIndex)
{
    bool bHasAlreadyBound = false;
    bool bSlotHasValue = false;
    
    TextureSlotMap::iterator it = _textureSlotMap.find(slotIndex);
    if(it != _textureSlotMap.end())
    {
        bSlotHasValue = true;
        
        TextureUUID alreadyBoundTexUUID = it->second;
        if(alreadyBoundTexUUID == texUUID)
        {
            alreadyBoundTexUUID = true;
        }
    }
    
    if(!bHasAlreadyBound)
    {
        Texture* texture = GetTextureWithUUID(texUUID);
        assert(texture != nullptr);
        texture->Bind(GL_TEXTURE0 + slotIndex);
        
        
        if(bSlotHasValue)
        {
            it->second = texUUID;
        }
        else
        {
            _textureSlotMap.insert(std::make_pair(slotIndex,texUUID));
        }
    }
}

}
