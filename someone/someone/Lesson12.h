#pragma once
#include "Ayy.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class AYYMesh;
}

class CommonNode;
class PhongTexMatNode;
class Lesson12 : public ayy::BaseScene
{
public:
    Lesson12(int viewportWidth,int viewportHeight);
    ~Lesson12();
    
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
    
    
    float       _rotSpeed  = 90;
    float       _lightRotSpeed = 45.0f;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    CommonNode*     _dummyLight = nullptr;
    PhongTexMatNode*   _obj = nullptr;
    
    float       _curLightDeg = 0;
    
    // bridge with ImGUI
    ayy::Vec3f  _lightAmbient;
    ayy::Vec3f  _lightDiffuse;
    ayy::Vec3f  _lightSpecular;
    
    float       _objShininess = 32.0f;
    float       _objCurScale = 2.0f;
    
    
    ayy::TextureUUID _texDiffuse = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID _texSpecular = ayy::TextureManager::kInvalidTextureUUID;
};
