#pragma once
#include "Ayy.h"
#include "RenderNode.h"

namespace ayy {
namespace model {
class Model;
}
namespace meshv2 {
class Model;
}
}



namespace crude {

class MeshRender : public RenderNode
{
public:
    MeshRender();
    virtual ~MeshRender();
    
    virtual void Initiate() override;
    virtual void CleanUp() override;
    
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix) override;
    
    void SetModel(ayy::model::Model* model);
    void SetModel2(ayy::meshv2::Model* model);
    
protected:
    ayy::ShaderProgram* _shader = nullptr;
    ayy::model::Model*  _model  = nullptr;
    ayy::meshv2::Model* _model2  = nullptr;
    
};

}

