#pragma once
#include <vector>
#include "PhongMultiLightMaterial.h"
#include "Ayy.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class AYYMesh;
}

class CommonNode;
class Lesson15BoxNode;
class Lesson15 : public ayy::BaseScene
{
public:
    Lesson15(int viewportWidth,int viewportHeight);
    ~Lesson15();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    virtual void OnUpdate() override;
    virtual void OnViewportSizeChanged(int width,int height) override;
    virtual void OnGUI() override;
    
protected:
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareTexture();
    
private:
    ayy::AYYMesh*       _boxMesh = nullptr;
    ayy::AYYMesh*       _planeMesh = nullptr;
    ayy::AYYMesh*       _quadMesh = nullptr;
    ayy::Camera*        _camera = nullptr;
    
    ayy::ShaderProgram*  _boxShader = nullptr;
    ayy::ShaderProgram*  _borderShader = nullptr;
    ayy::ShaderProgram*  _planeShader = nullptr;
    ayy::ShaderProgram*  _windowShader = nullptr;
    ayy::ShaderProgram*  _postProcessShader = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    std::vector<CommonNode*>    _boxes;
    std::vector<CommonNode*>    _borders;
    CommonNode*                 _planeNode = nullptr;
    std::vector<CommonNode*>    _windows;
    CommonNode*                 _postProcessNode = nullptr;
    
    ayy::TextureUUID _boxTexture1 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _boxTexture2 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _planeTexture = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _windowTexture = ayy::TextureManager::kInvalidTextureUUID;
};
