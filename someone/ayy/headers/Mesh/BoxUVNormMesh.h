#pragma once
#include "AYYMesh.h"

namespace ayy {

class BoxUVNormMesh : public AYYMesh
{
public:
    BoxUVNormMesh();
    virtual ~BoxUVNormMesh();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void Draw() override;
    
    void Bind() override;
    void UnBind() override;
    
    virtual int GetIndexCount() override;
    
protected:
    GLuint _vao,_vbo,_ebo;
    int     _indexCount = 0;
};

}


