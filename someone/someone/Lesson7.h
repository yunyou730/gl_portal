#pragma once
#include "BaseScene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureManager.h"

namespace ayy
{
class ShaderProgram;
class Texture;
}

class Lesson7 : public ayy::BaseScene
{
public:
    ~Lesson7();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void OnRender() override;
    
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
};
