#pragma once
#include "Batch.h"

namespace ayy {
class PlaneBatch : public Batch
{
public:
    PlaneBatch();
    virtual ~PlaneBatch();
    
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
