#pragma once
#include "Ayy.h"
#include <vector>

class Lesson16PostProcessNode;
class SkyBoxNode;
class Lesson19 : public ayy::BaseScene
{
public:
    Lesson19(int viewportWidth,int viewportHeight);
    ~Lesson19();
    
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
    ayy::AYYFrameBuffer*    _frameBuffer = nullptr;
    
    ayy::AYYMesh*       _boxMesh = nullptr;
    ayy::AYYMesh*       _planeMesh = nullptr;
    ayy::AYYMesh*       _quadMesh = nullptr;
    ayy::AYYMesh*       _skyBoxMesh = nullptr;
//    ayy::AYYMesh*       _modelMesh = nullptr;
    
    ayy::Camera*        _camera = nullptr;
    
    ayy::ShaderProgram*  _boxShader = nullptr;
    ayy::ShaderProgram*  _borderShader = nullptr;
    ayy::ShaderProgram*  _planeShader = nullptr;
    ayy::ShaderProgram*  _windowShader = nullptr;
    ayy::ShaderProgram*  _postProcessShader = nullptr;
    ayy::ShaderProgram*  _skyBoxShader = nullptr;
    ayy::ShaderProgram*  _mainBoxShader = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    std::vector<ayy::CommonNode*>    _boxes;
    std::vector<ayy::CommonNode*>    _borders;
    ayy::CommonNode*                 _planeNode = nullptr;
    std::vector<ayy::CommonNode*>    _windows;
    Lesson16PostProcessNode*    _postProcessNode = nullptr;
    SkyBoxNode*                 _skyBoxNode = nullptr;
    ayy::CommonNode*                 _mainNode = nullptr;
//    CommonNode*                 _modelNode = nullptr;
    
    ayy::TextureUUID _boxTexture1 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _boxTexture2 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _planeTexture = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _windowTexture = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _skyboxTexture = ayy::TextureManager::kInvalidTextureUUID;
    
    int _selectPostProcess = 0;
};
