#include "Lesson15.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Mesh/PlaneUVMesh.h"
#include "../ayy/headers/Mesh/BoxMesh.h"
#include "../ayy/headers/Common.h"
#include "AyyImGUI.h"
#include "../ayy/headers/Mesh/BoxUVNormMesh.h"
#include "PhongMultLightNode.h"
#include "PhongMultiLightMaterial.h"
#include "Lesson15Nodes.h"

static const int kBoxCount = 7;
static const int kBoxPosClamp = 5;

static const ayy::Vec3f kCameraDefaultPos(0,0,-7);

Lesson15::Lesson15(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
}

Lesson15::~Lesson15()
{

}

void Lesson15::Prepare()
{
    // meshes
    _boxMesh = new ayy::BoxUVNormMesh();
    _boxMesh->Prepare();
    
    _planeMesh = new ayy::PlaneUVMesh();
    _planeMesh->Prepare();
    
    // textures
    PrepareTexture();
    
    // shaders
    _boxShader = ayy::Util::CreateShaderWithFile("res/lesson15_box.vs","res/lesson15_box.fs");
    _planeShader = ayy::Util::CreateShaderWithFile("res/lesson15_plane.vs","res/lesson15_plane.fs");
    _borderShader = ayy::Util::CreateShaderWithFile("res/lesson15_single_color.vs","res/lesson15_single_color.fs");
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
//    _camera->SetNear(0.3);
//    _camera->SetNear(15.0);
    _camera->SetPos(kCameraDefaultPos);
    
    // boxes
    for(int i = 0;i < kBoxCount;i++)
    {
        // box
        CommonNode* node = new Lesson15BoxNode();
        node->SetShader(_boxShader);
        node->SetMesh(_boxMesh);
        
        float x = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        float z = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        node->SetPosition(ayy::Vec3f(x,0,z));
        
        _boxes.push_back(node);
        
        
        // border
        CommonNode* borderNode = new Lesson15BorderNode();
        borderNode->SetShader(_borderShader);
        borderNode->SetMesh(_boxMesh);
        borderNode->SetPosition(ayy::Vec3f(x,0,z));
        borderNode->SetScale(ayy::Vec3f(1.1,1.1,1.1));
        _borders.push_back(borderNode);
    }
    
    // plane node
    _planeNode = new Lesson15PlaneNode();
    _planeNode->SetShader(_planeShader);
    _planeNode->SetMesh(_planeMesh);
    
    _planeNode->SetScale(ayy::Vec3f(20.0,1.0,20.0));
    _planeNode->SetPosition(ayy::Vec3f(-10.0,-0.51f,-10.0));
}

void Lesson15::Cleanup()
{
    _boxMesh->Cleanup();
    AYY_SAFE_DEL(_boxMesh);
    
    _planeMesh->Cleanup();
    AYY_SAFE_DEL(_planeMesh);
    
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_boxShader);
    AYY_SAFE_DEL(_planeShader);
    AYY_SAFE_DEL(_borderShader);
    
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        CommonNode* box = *it;
        AYY_SAFE_DEL(box);
    }
    _boxes.clear();
    
    for(auto it = _borders.begin();it != _borders.end();it++)
    {
        AYY_SAFE_DEL(*it);
    }
    _borders.clear();
    
    AYY_SAFE_DEL(_planeNode);
}

void Lesson15::OnUpdate()
{
    // @miao @todo
    
}

void Lesson15::OnRender()
{
    // gl settings
//    glClearStencil(0);  //  设置 用什么值, 在 glClear 的时候 来清空 模版缓冲区 .不写默认是 0
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    
    // draw plane
    glStencilMask(0x00);    //  禁止写入 stencil buffer
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_planeTexture,0);
    _planeNode->OnRender(_camera);
    

    // draw boxes
    glStencilFunc(GL_ALWAYS,1,0xff);
    glStencilMask(0xff);    // 允许写入 stencil buffer
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_boxTexture1,0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_boxTexture2,1);
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        CommonNode* box = *it;
        box->OnRender(_camera);
    }
    
    
    // draw box borders
    glStencilFunc(GL_NOTEQUAL,1,0xff);
    glStencilMask(0x00);    // 禁止 写入 stencil buffer
//    glDisable(GL_DEPTH_TEST);
    for(auto it = _borders.begin();it != _borders.end();it++)
    {
        (*it)->OnRender(_camera);
    }
    
    //  恢复绘制
    glStencilMask(0xff);    // 允许写入
    glEnable(GL_DEPTH_TEST);
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
