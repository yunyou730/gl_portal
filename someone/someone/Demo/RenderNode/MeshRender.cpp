#include "MeshRender.h"
#include "../Manager/ShaderManager.h"
#include "Ayy.h"
#include "ModelImporter.h"

namespace crude {

MeshRender::MeshRender()
{
    
}

MeshRender::~MeshRender()
{
    
}

void MeshRender::Initiate()
{
    _shader = BaseManager::GetInstance<ShaderManager>()->LoadProgram("res/demo/model.vs","res/demo/model.fs");
}

void MeshRender::CleanUp()
{
    
}

void MeshRender::OnUpdate(float deltaTime)
{
    
}

void MeshRender::OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix)
{
    if(_model != nullptr)
    {
        _shader->Use();
        _shader->SetUniformMat4x4("u_Model",(GLfloat*)worldMatrix->data);
        _shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
        _shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
        _shader->SetUniform("u_TestColor",false);
        _model->DoDraw();
    }
    
    if(_model2 != nullptr)
    {
        _shader->Use();
        _shader->SetUniformMat4x4("u_Model",(GLfloat*)worldMatrix->data);
        _shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
        _shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
        _shader->SetUniform("u_TestColor",true);
        _model2->DoDraw();
    }
}

void MeshRender::SetModel(ayy::model::Model* model)
{
    _model = model;
}

void MeshRender::SetModel2(ayy::meshv2::Model* model)
{
    _model2 = model;
}

}


