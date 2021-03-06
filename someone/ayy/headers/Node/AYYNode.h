#pragma once

#include <vector>

namespace ayy
{
class ShaderProgram;
class Texture;
class Camera;
class Batch;
}

namespace ayy
{
class Node
{
public:
    Node();
    virtual ~Node();
    
    virtual void OnCreate() = 0;
    virtual void OnUpdate(float dt);
    virtual void OnCleanUp()= 0;
    virtual void OnRender(ayy::Camera* mainCam) = 0;
};

}



