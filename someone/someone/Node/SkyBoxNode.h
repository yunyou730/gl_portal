#pragma once

#include "CommonNode.h"

class SkyBoxNode : public CommonNode
{
public:
    void SetTexture(ayy::TextureUUID texUUID)
    {
        _texUUID = texUUID;
    }
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam) override;
    virtual void AfterDraw() override;
    
private:
    ayy::TextureUUID _texUUID = ayy::TextureManager::kInvalidTextureUUID;
};


