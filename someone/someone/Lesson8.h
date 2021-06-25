#pragma once
#include "LessonBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"
#include "Math.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class Node;
}

class Lesson8 : public LessonBase
{
public:
    Lesson8(int viewportWidth,int viewportHeight);
    ~Lesson8();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender(float deltaTime) override;
    
protected:
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareTexture();
    
private:
    void UpdateTransform(float deltaTime);
    
private:
    ayy::Node*   _node = nullptr;
    
    ayy::ShaderProgram*  _shader = nullptr;
    
    ayy::TextureUUID   _texture1 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID   _texture2 = ayy::TextureManager::kInvalidTextureUUID;
    
    
    float       _rotSpeed  = 90;
    ayy::Vec3f  _rot;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed   = 1.0f;
    float   _camRotSpeed    = 45.0f;
};
