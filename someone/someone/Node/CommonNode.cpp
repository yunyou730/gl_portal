#include "CommonNode.h"

#include "../../ayy/headers/Util.h"
#include "../../ayy/headers/Shader.h"
#include "TextureManager.h"
#include "../../ayy/headers/Batch/TestBatch.h"
#include "../../ayy/headers/Common.h"

#include <sstream>

static const std::string textureUniformNamePrefix = "texture";
static const ayy::Vec3f kDefaultRotAxis(0,1,0);
static const ayy::Vec3f kDefaultScale(1,1,1);

CommonNode::CommonNode()
{
    _scale = kDefaultScale;
    _rotAxis = kDefaultRotAxis;
}

CommonNode::~CommonNode()
{
    
}

void CommonNode::AddTex(ayy::TextureUUID texId)
{
    _texIDs.push_back(texId);
}

void CommonNode::SetShader(ayy::ShaderProgram* shader)
{
    _shader = shader;
}

void CommonNode::SetBatch(ayy::Batch* batch)
{
    _batch = batch;
}

void CommonNode::OnCreate()
{
    
}

void CommonNode::OnUpdate(float dt)
{
    
}

void CommonNode::OnRender(ayy::Camera* mainCam)
{
    // shader
    _shader->Use();
    
    // using texture
    for(int i = 0;i < _texIDs.size();i++)
    {
        ayy::TextureManager::GetInstance()->BindTextureToSlot(_texIDs[i],i);
        std::stringstream ssUniformName;
        ssUniformName << textureUniformNamePrefix << i + 1;
        _shader->SetUniform(ssUniformName.str(),i);
    }
    
    // set shader values
    SyncPropToShader(mainCam);
    
    // draw batch
    _batch->Bind();
    _batch->Draw();
    
    // after draw
    _batch->UnBind();
    _shader->UnUse();
}

void CommonNode::OnCleanUp()
{
    
}

void CommonNode::SetPosition(float x,float y,float z)
{
    _pos.SetX(x);    _pos.SetY(y);    _pos.SetZ(z);
}

//void CommonNode::SetRotation(float rx,float ry,float rz)
//{
//    _rot.SetX(rx);    _rot.SetY(ry);    _rot.SetZ(rz);
//}

void CommonNode::SetRotation(float deg)
{
    _rot = deg;
}

void CommonNode::SetRotAxis(const ayy::Vec3f& axis)
{
    assert(axis.Length() > 0);
    _rotAxis = axis.GetNormalize();
}

void CommonNode::SetScale(const ayy::Vec3f scale)
{
    _scale = scale;
}

void CommonNode::SetScale(float scale)
{
    _scale.SetX(scale);
    _scale.SetY(scale);
    _scale.SetZ(scale);
}

void CommonNode::SyncPropToShader(ayy::Camera* mainCam)
{
    ayy::Mat4x4f matScale;
    ayy::Mat4x4f matTranslate;
    ayy::Mat4x4f matRot;
    
    ayy::MakeTranslateMatrix(matTranslate,_pos.x(),_pos.y(),_pos.z());
    ayy::MakeScaleMatrix(matScale, _scale.x(),_scale.y(),_scale.z());
    ayy::MakeRotateByAxisMatrix(matRot,_rotAxis,ayy::DegToRad(_rot));
    
    ayy::Mat4x4f matModel = matScale * matRot * matTranslate;
    _shader->SetUniformMat4x4("u_Model",(GLfloat*)matModel.data);
    
    
    // view projection
    _shader->SetUniformMat4x4("u_View", (GLfloat*)mainCam->GetViewMatrix().data);
    _shader->SetUniformMat4x4("u_Projection", (GLfloat*)mainCam->GetProjMatrix().data);
}
