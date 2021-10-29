#pragma once
#include "Ayy.h"
#include "RenderNode.h"
#include <string>

namespace crude {

struct SkyboxTextureParam
{
    std::string frontImagePath;
    std::string backImagePath;
    std::string upImagePath;
    std::string bottomImagePath;
    std::string leftImagePath;
    std::string rightImagePath;
    
    SkyboxTextureParam(const std::string& front,
                       const std::string& back,
                       const std::string& up,
                       const std::string& bottom,
                       const std::string& left,
                       const std::string& right)
        :frontImagePath(front)
        ,backImagePath(back)
        ,upImagePath(up)
        ,bottomImagePath(bottom)
        ,leftImagePath(left)
        ,rightImagePath(right)
    {}
    
    SkyboxTextureParam(const SkyboxTextureParam& other)
    {
        operator=(other);
    }
    
    void operator= (const SkyboxTextureParam& other)
    {
        frontImagePath  = other.frontImagePath;
        backImagePath   = other.backImagePath;
        upImagePath     = other.upImagePath;
        bottomImagePath = other.bottomImagePath;
        leftImagePath   = other.leftImagePath;
        rightImagePath  = other.rightImagePath;
    }
};

class SkyboxRenderNode : public RenderNode
{
public:
    SkyboxRenderNode(const SkyboxTextureParam& textureParam);
    virtual ~SkyboxRenderNode();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix) override;
    
    ayy::ShaderProgram* GetShader() { return _shader;}
    
protected:
    void PrepareMesh();
    
protected:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    ayy::ShaderProgram* _shader = nullptr;
    
    SkyboxTextureParam _textureParam;
    ayy::TextureUUID _cubeTex = ayy::TextureManager::kInvalidTextureUUID;
};

}
