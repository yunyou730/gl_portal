#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "TextureManager.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class Batch;
}

class Node
{
public:
    Node();
    virtual ~Node();
    
    virtual void OnCreate() = 0;
    virtual void OnUpdate(float dt);
    virtual void OnRender(ayy::Camera* mainCam);
    virtual void OnCleanUp()= 0;
    
//protected:
//    ayy::Batch* _batch = nullptr;
//    ayy::ShaderProgram* _shader = nullptr;
//    std::vector<ayy::TextureUUID> _textureIDs;
};



