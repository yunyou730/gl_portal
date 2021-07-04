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
    ayy::Batch*     _groundBatch = nullptr;
    ayy::Batch*     _boxBatch = nullptr;
    ayy::Batch*     _objBatch = nullptr;
    
    ayy::ShaderProgram*  _groundShader = nullptr;
    ayy::ShaderProgram*  _dummyLightShader = nullptr;
    ayy::ShaderProgram*  _phongShader = nullptr;
    
    
    float       _rotSpeed  = 90;
    float       _lightRotSpeed = 45.0f;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 7.0f;
    float   _camRotSpeed    = 120;
    
    CommonNode*     _ground = nullptr;
    CommonNode*     _dummyLight = nullptr;
    PhongMatNode*   _obj = nullptr;
    
    float       _curLightDeg = 0;
    
    // bridge with ImGUI
    ayy::Vec3f  _lightAmbient;
    ayy::Vec3f  _lightDiffuse;
    ayy::Vec3f  _lightSpecular;
    
    ayy::Vec3f  _objAmbient;
    ayy::Vec3f  _objDiffuse;
    ayy::Vec3f  _objSpecular;
    float       _objShininess = 32.0f;
    float       _objCurScale = 2.0f;
};
