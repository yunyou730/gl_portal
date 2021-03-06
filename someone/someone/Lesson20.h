#pragma once
#include "Ayy.h"
#include <vector>

class Lesson20NormalMapNode;
class SkyBoxNode;
class Lesson20 : public ayy::BaseScene
{
public:
    Lesson20(int viewportWidth,int viewportHeight);
    ~Lesson20();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    virtual void OnUpdate() override;
    virtual void OnViewportSizeChanged(int width,int height) override;
    virtual void OnGUI() override;
    
protected:
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
    void DrawScene();
    void DrawPostProcess();
    
protected:
    void Prepare2DTexture();
    void PrepareCubeTexture();
    
private:
    ayy::AYYMesh*       _planeMesh = nullptr;
    ayy::AYYMesh*       _quadMesh = nullptr;
    ayy::AYYMesh*       _skyBoxMesh = nullptr;
    ayy::AYYMesh*       _boxMesh = nullptr;
    
    ayy::Camera*        _camera = nullptr;
    
    ayy::ShaderProgram*  _planeShader = nullptr;
    ayy::ShaderProgram*  _skyBoxShader = nullptr;
    ayy::ShaderProgram*  _wallShader = nullptr;
    ayy::ShaderProgram*  _dummyLightShader = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    SkyBoxNode*                      _skyBoxNode = nullptr;
    Lesson20NormalMapNode*          _wallNode = nullptr;
    ayy::CommonNode*                 _dummyLightNode = nullptr;
    
    ayy::TextureUUID _planeTexture = ayy::TextureManager::kInvalidTextureUUID;
//    ayy::TextureUUID _windowTexture = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _skyboxTexture = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _wallDiffuse = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _wallNormalMap = ayy::TextureManager::kInvalidTextureUUID;
    
    int _selectPostProcess = 0;
};
