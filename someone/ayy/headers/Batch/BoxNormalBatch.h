#include "Batch.h"
#include "../TextureManager.h"

namespace ayy {

class BoxNormalBatch : public Batch
{
public:
    BoxNormalBatch();
    virtual ~BoxNormalBatch();
    
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

