#include "Node.h"
#include "../TextureManager.h"

namespace ayy {

class TestNode : public Node
{
public:
    TestNode();
    virtual ~TestNode();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void Draw() override;
    
//    void SetTextures(ayy::TextureUUID tex1,ayy::TextureUUID tex2);
    
    void Bind() override;
    void UnBind() override;
    
    virtual int GetIndexCount() override;
    
protected:
    GLuint _vao,_vbo,_ebo;
    
//    ayy::TextureUUID   _texture1 = ayy::TextureManager::kInvalidTextureUUID;
//    ayy::TextureUUID   _texture2 = ayy::TextureManager::kInvalidTextureUUID;
};

}


