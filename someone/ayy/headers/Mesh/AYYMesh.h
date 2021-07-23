#pragma once
#include <glad/glad.h>

namespace ayy
{
class AYYMesh
{
public:
    AYYMesh();
    virtual ~AYYMesh();
        
    virtual void Prepare() = 0;
    virtual void Cleanup() = 0;
    virtual void Draw() = 0;
    
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    
    virtual int GetIndexCount() = 0;
};

}
