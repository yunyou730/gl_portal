#pragma once
#include "Ayy.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class AYYMesh;
}

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
    ayy::AYYMesh*     _batch = nullptr;
    ayy::AYYMesh*     _groundBatch = nullptr;
    ayy::AYYMesh*     _boxBatch = nullptr;
    ayy::AYYMesh*     _boxNormalBatch = nullptr;
    
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
    
    ayy::CommonNode*     _box1 = nullptr;
    ayy::CommonNode*     _box2 = nullptr;
    ayy::CommonNode*     _ground = nullptr;
    ayy::CommonNode*     _dummyLight = nullptr;
    PhongMatNode*   _obj = nullptr;
    
    ayy::Vec3f      _curLightPos;
    float       _curLightDeg = 0;
};
