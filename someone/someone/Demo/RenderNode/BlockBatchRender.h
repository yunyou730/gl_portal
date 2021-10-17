#pragma once
#include "Ayy.h"
#include "RenderNode.h"
#include <vector>

namespace crude {

class BlockBatchRender : public RenderNode
{
public:
    BlockBatchRender();
    virtual ~BlockBatchRender();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix) override;
    
    
    void AddDrawInstance(const ayy::Vec3f& offset);
    void ModifyDrawInstance(int index,const ayy::Vec3f& offset);
    
protected:
    void PrepareMesh();
    bool IsDirty() const { return _bDirty;}
    void SetDirty(bool bDirty) {_bDirty = bDirty;}
    void RefreshInstanceData();
    
protected:
    GLuint _vao,_vbo,_ebo;
    GLuint _vboOffset;
    ayy::ShaderProgram* _shader = nullptr;
    std::vector<ayy::Vec3f> _instanceDatas;
    
    bool    _bDirty = false;
};

}

