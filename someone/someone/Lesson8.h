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
class Lesson8 : public ayy::BaseScene
{
public:
    Lesson8(int viewportWidth,int viewportHeight);
    ~Lesson8();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    virtual void OnUpdate() override;
    
protected:
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareTexture();
    
private:
    ayy::Batch*     _batch = nullptr;
    ayy::Batch*     _groundBatch = nullptr;
    
    ayy::ShaderProgram*  _commonShader = nullptr;
    ayy::ShaderProgram*  _groundShader  = nullptr;
    
    ayy::TextureUUID   _texture1 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID   _texture2 = ayy::TextureManager::kInvalidTextureUUID;
    
    float       _rotSpeed  = 90;
    ayy::Vec3f  _rot;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 180;
    
    float   _box1Rot = 0;
    
    CommonNode*     _box1 = nullptr;
    CommonNode*     _box2 = nullptr;
    CommonNode*     _ground = nullptr;
};
