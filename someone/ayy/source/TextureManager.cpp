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
    printf("CreateTextureWithFilePath:%s\n",filePath.c_str());
    
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
    ayy::Texture2D* tex = new ayy::Texture2D(uuid,raw);
    
    _textureMap.insert(std::make_pair(uuid,tex));
    
    return uuid;
}

TextureUUID TextureManager::CreateRenderTexture(int width,int height)
{
    TextureUUID uuid = NextUUID();
    ayy::Texture2D* tex = new ayy::Texture2D(uuid,width,height);
    _textureMap.insert(std::make_pair(uuid,tex));
    return uuid;
}

TextureUUID TextureManager::CreateCubeTexture(const std::string& right,
                              const std::string& left,
                              const std::string& top,
                              const std::string& bottom,
                              const std::string& back,
                              const std::string& front)
{
    TextureUUID uuid = NextUUID();
    ayy::BaseTexture* tex = new ayy::TextureCube(uuid,left,top,top,bottom,back,front);
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

ayy::BaseTexture* TextureManager::GetTextureWithUUID(TextureUUID uuid)
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
            bHasAlreadyBound = true;
        }
    }
    
    if(!bHasAlreadyBound)
    {
        ayy::BaseTexture* texture = GetTextureWithUUID(texUUID);
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

void TextureManager::BindTextureToCube(TextureUUID texUUID)
{
    ayy::BaseTexture* cubTex = _textureMap.find(texUUID)->second;
    cubTex->Bind();
}

}
