#pragma once
#include "LessonBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
}

class Lesson8 : public LessonBase
{
public:
    ~Lesson8();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender(float deltaTime) override;
    
protected:
    virtual void HandleKeyboardInput(GLFWwindow* window) override;
    
protected:
    void PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO);
    void PrepareTexture();
    
private:
    void UpdateTransform(float deltaTime);
    
private:
    GLuint  _vao,_vbo,_ebo;
    ayy::ShaderProgram*  _shader = nullptr;
    
    ayy::TextureUUID   _texture1 = ayy::TextureManager::kInvalidTextureUUID;
    ayy::TextureUUID   _texture2 = ayy::TextureManager::kInvalidTextureUUID;
    
    float   _rotZ       = 0.0f;
    float   _rotZSpeed  = 90;
    
    ayy::Camera*  _camera = nullptr;
    
    float   _camMoveSpeed = 0.5f;
    float   _camRotSpeed = 45.0f;   
};
