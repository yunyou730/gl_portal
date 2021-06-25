#pragma once
#include <glad/glad.h>

namespace ayy
{
class Node
{
public:
    Node();
    virtual ~Node();
        
    virtual void Prepare() = 0;
    virtual void Cleanup() = 0;
    virtual void Draw() = 0;
    
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    
    virtual int GetIndexCount() = 0;
};

}
