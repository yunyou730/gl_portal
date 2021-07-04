#pragma once
#include "BaseScene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"
#include "Math.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class Batch;
}

class CommonNode;
class PhongMatNode;
class Lesson10 : public ayy::BaseScene
{
public:
    Lesson10(int viewportWidth,int viewportHeight);
    ~Lesson10();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    virtual void OnUpdate() override;
    virtual void OnViewportSizeChanged(int width,int height) override;
    
protected:
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareTexture();
    
private:
    ayy::Batch*     _batch = nullptr;
    ayy::Batch*     _groundBatch = nullptr;
    ayy::Batch*     _boxBatch = nullptr;
    ayy::Batch*     _boxNormalBatch = nullptr;
    
    ayy::ShaderProgram*  _commonShader = nullptr;
    ayy::ShaderProgram*  _groundShader = nullptr;
    ayy::ShaderProgram*  _dummyLightShader = nullptr;
    ayy::ShaderProgram*  _phongShader = nullptr;
    
    ayy::TextureUUID   _texture1 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID   _texture2 = ayy::TextureManager::kInvalidTextureUUID;
    
    float       _rotSpeed  = 90;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    CommonNode*     _box1 = nullptr;
    CommonNode*     _box2 = nullptr;
    CommonNode*     _ground = nullptr;
    CommonNode*     _dummyLight = nullptr;
    PhongMatNode*   _obj = nullptr;
    
    ayy::Vec3f      _curLightPos;
    float       _curLightDeg = 0;
};