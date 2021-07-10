#pragma once
#include "BaseScene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"
#include "Math.h"
#include <vector>
#include "PhongMultiLightMaterial.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class Batch;
}

class CommonNode;
class PhongMultLightNode;
class Lesson13 : public ayy::BaseScene
{
public:
    Lesson13(int viewportWidth,int viewportHeight);
    ~Lesson13();
    
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
    ayy::Batch*     _boxBatch = nullptr;
    ayy::Batch*     _objBatch = nullptr;
    
    ayy::ShaderProgram*  _dummyLightShader = nullptr;
    ayy::ShaderProgram*  _phongShader = nullptr;
    
    float       _lightRotSpeed = 45.0f;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    CommonNode*                         _dummyLight = nullptr;
    std::vector<PhongMultLightNode*>    _boxes;
    
    float       _curLightDeg = 0;
    
    
    ayy::TextureUUID _texDiffuse = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _texSpecular = ayy::TextureManager::kInvalidTextureUUID;
    
    
    
    float       _objShininess   = 32.0f;
    float       _objCurScale    = 1.5f;
    
    DirectionLight  _dirLightParam;
    PointLight      _pointLightParam;
    SpotLight       _spotLightParam;
};
