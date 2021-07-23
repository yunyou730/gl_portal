#include "Lesson15.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Mesh/TestMesh.h"
#include "../ayy/headers/Mesh/PlaneMesh.h"
#include "../ayy/headers/Mesh/BoxMesh.h"
#include "../ayy/headers/Common.h"
#include "AyyImGUI.h"
#include "../ayy/headers/Mesh/BoxUVNormMesh.h"
#include "PhongMultLightNode.h"
#include "PhongMultiLightMaterial.h"
#include "Lesson15BoxNode.h"

static const int kBoxCount = 7;
static const int kBoxPosClamp = 5;

static const ayy::Vec3f kCameraDefaultPos(0,0,-7);

Lesson15::Lesson15(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
}

Lesson15::~Lesson15()
{
    AYY_SAFE_DEL(_boxBatch);
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        CommonNode* box = *it;
        AYY_SAFE_DEL(box);
    }
    _boxes.clear();
}

void Lesson15::Prepare()
{
    // meshes
    _boxBatch = new ayy::BoxUVNormMesh();
    _boxBatch->Prepare();
    
    _planeMesh = new ayy::PlaneMesh();
    _planeMesh->Prepare();
    
    // textures
    PrepareTexture();
    
    // shaders
    _boxShader = ayy::Util::CreateShaderWithFile("res/lesson15_box.vs","res/lesson15_box.fs");
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(kCameraDefaultPos);
    
    // boxs
    for(int i = 0;i < kBoxCount;i++)
    {
        CommonNode* node = new Lesson15BoxNode();
        node->SetShader(_boxShader);
        node->SetMesh(_boxBatch);
        
        float x = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        float z = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        node->SetPosition(ayy::Vec3f(x,0,z));
        
        _boxes.push_back(node);
    }
    
    
}

void Lesson15::Cleanup()
{
    _boxBatch->Cleanup();
    AYY_SAFE_DEL(_boxBatch);
    
    _planeMesh->Cleanup();
    AYY_SAFE_DEL(_planeMesh);
    
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_boxShader);
}

void Lesson15::OnUpdate()
{
    // @miao @todo
    
}

void Lesson15::OnRender()
{
    
    // draw boxes
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_boxTexture1,0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_boxTexture2,1);
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        CommonNode* box = *it;
        box->OnRender(_camera);
    }
    
    
    // draw plane
    
    
}

void Lesson15::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

void Lesson15::PrepareTexture()
{
    _boxTexture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/box_diffuse.png");
    _boxTexture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/emoji_wa.png");
    _planeTexture = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/marble.jpg");
    
    // @miao @todo
    // 这一步绑定 是不是应该在绘制之前再绑 ?
//    ayy::TextureManager::GetInstance()->BindTextureToSlot(_boxTexture1,0);
//    ayy::TextureManager::GetInstance()->BindTextureToSlot(_boxTexture2,1);
}

void Lesson15::HandleKeyboardInput(GLFWwindow* window)
{
    // handle camera move
    float delta = GetDeltaTime() * _camMoveSpeed;
    float deltaRot = GetDeltaTime() * _camRotSpeed;
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = delta * _camera->GetLookDir();
        _camera->TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = -delta * _camera->GetLookDir();
        _camera->TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = -delta * _camera->GetRightDir();
        _camera->TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = delta * _camera->GetRightDir();
        _camera->TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        _camera->TakeYaw(-deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        _camera->TakeYaw(deltaRot);
    }
    
    // mouse input
    delta = _camRotSpeed * GetDeltaTime();
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        _camera->TakePitch(-deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        _camera->TakePitch(deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        _camera->TakeYaw(-deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        _camera->TakeYaw(deltaRot);
    }
}

void Lesson15::OnGUI()
{
    BaseScene::OnGUI();
        

}
