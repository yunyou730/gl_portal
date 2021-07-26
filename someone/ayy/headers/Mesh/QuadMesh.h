#pragma once
#include "AYYMesh.h"

namespace ayy {
class QuadMesh : public AYYMesh
{
public:
    QuadMesh();
    virtual ~QuadMesh();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void Draw() override;
    
    void Bind() override;
    void UnBind() override;
    
    virtual int GetIndexCount() override;
    
protected:
    GLuint  _vao,_vbo,_ebo;
};

}
