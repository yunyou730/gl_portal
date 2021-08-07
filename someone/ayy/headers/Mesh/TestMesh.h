#include "AYYMesh.h"

namespace ayy {

class TestMesh : public AYYMesh
{
public:
    TestMesh();
    virtual ~TestMesh();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void Draw() override;
    
    void Bind() override;
    void UnBind() override;
    
    virtual int GetIndexCount() override;
    
protected:
    GLuint _vao,_vbo,_ebo;
};

}
