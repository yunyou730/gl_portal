#pragma once
#include "Ayy.h"

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
    ayy::AYYMesh*     _batch = nullptr;
    ayy::AYYMesh*     _groundBatch = nullptr;
    
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
    
    ayy::CommonNode*     _box1 = nullptr;
    ayy::CommonNode*     _box2 = nullptr;
    ayy::CommonNode*     _ground = nullptr;
};
