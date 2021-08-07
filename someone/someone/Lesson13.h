#pragma once
#include "BaseScene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AYYTextureManager.h"
#include "Math.h"
#include <vector>
#include "PhongMultiLightMaterial.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class AYYMesh;
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
    ayy::AYYMesh*     _boxBatch = nullptr;
    ayy::AYYMesh*     _objBatch = nullptr;
    
    ayy::ShaderProgram*  _dummyLightShader = nullptr;
    ayy::ShaderProgram*  _phongShader = nullptr;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    CommonNode*                         _dummyLight = nullptr;
    std::vector<PhongMultLightNode*>    _boxes;
    
    
    ayy::TextureUUID _texDiffuse = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _texSpecular = ayy::TextureManager::kInvalidTextureUUID;
    
    
    
    float       _objShininess   = 32.0f;
    float       _objCurScale    = 1.5f;
    
    DirectionLight  _dirLightParam;
    PointLight      _pointLightParam;
    SpotLight       _spotLightParam;
    
    bool        _bEnableDirLight = false;
    bool        _bEnablePointLight = true;
    bool        _bEnableSpotLight = true;
    
    ayy::Vec3f  _pointLightPos;
};
