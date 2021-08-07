#include "Lesson15.h"
#include "PhongMultLightNode.h"
#include "PhongMultiLightMaterial.h"
#include "LessonSpecialNodes.h"

static const int kBoxCount = 7;
static const int kBoxPosClamp = 5;
static const int kWindowsCount = 20;

static const ayy::Vec3f kCameraDefaultPos(0,0,-7);
static const float kBorderScale = 1.1f;

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
    
    _quadMesh = new ayy::QuadMesh();
    _quadMesh->Prepare();
    
    // textures
    PrepareTexture();
    
    // shaders
    _boxShader = ayy::Util::CreateShaderWithFile("res/lesson15_box.vs","res/lesson15_box.fs");
    _planeShader = ayy::Util::CreateShaderWithFile("res/lesson15_plane.vs","res/lesson15_plane.fs");
    _borderShader = ayy::Util::CreateShaderWithFile("res/lesson15_single_color.vs","res/lesson15_single_color.fs");
    _windowShader = ayy::Util::CreateShaderWithFile("res/lesson15_window.vs","res/lesson15_window.fs");
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
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
        borderNode->SetScale(ayy::Vec3f(kBorderScale,kBorderScale,kBorderScale));
        _borders.push_back(borderNode);
    }
    
    // windows node
    for(int i = 0;i < kWindowsCount;i++)
    {
        CommonNode* node = new Lesson15WindowNode();
        node->SetShader(_windowShader);
        node->SetMesh(_planeMesh);
        
        float x = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        float z = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        node->SetPosition(ayy::Vec3f(x,0.5,z));
        node->SetRotAxis(ayy::Vec3f(1,0,0));
        node->SetRotation(90);
        
        _windows.push_back(node);
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
    
    _quadMesh->Cleanup();
    AYY_SAFE_DEL(_quadMesh);
    
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_boxShader);
    AYY_SAFE_DEL(_planeShader);
    AYY_SAFE_DEL(_borderShader);
    AYY_SAFE_DEL(_windowShader);
    
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
    
    for(auto it = _windows.begin();it != _windows.end();it++)
    {
        AYY_SAFE_DEL(*it);
    }
    _windows.clear();
    
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
    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
    
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    
    
    // draw plane
//    glDisable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glStencilMask(0x00);    //  禁止写入 stencil buffer
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_planeTexture,0);
    _planeNode->OnRender(_camera);
    
    
    
    // draw boxes
//    glDisable(GL_STENCIL_TEST);
    glDisable(GL_CULL_FACE);
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
    glDisable(GL_CULL_FACE);
    glStencilFunc(GL_NOTEQUAL,1,0xff);
    glStencilMask(0x00);    // 禁止 写入 stencil buffer
//    glDisable(GL_CULL_FACE);
    for(auto it = _borders.begin();it != _borders.end();it++)
    {
        (*it)->OnRender(_camera);
    }
    
    

    // draw windows
    glDisable(GL_CULL_FACE);
    glStencilMask(0x00);
    glStencilFunc(GL_ALWAYS,1,0xff);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_windowTexture,0);
    std::sort(_windows.begin(),_windows.end(),[&](CommonNode* a,CommonNode* b){
        float disA = (_camera->GetPos() - a->GetPosition()).Length();
        float disB = (_camera->GetPos() - a->GetPosition()).Length();
        return disA >= disB;
    });
    for(auto it = _windows.begin();it != _windows.end();it++)
    {
        auto win = *it;
        win->OnRender(_camera);
    }

    
    //  恢复绘制
    glStencilMask(0xff);    // 允许写入
//    glEnable(GL_DEPTH_TEST);
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
    _windowTexture = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/blending_transparent_window.png");
    
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
