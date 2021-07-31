#include "Lesson17.h"
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
#include "LessonSpecialNodes.h"
#include "AYYFrameBuffer.h"
#include "../ayy/headers/Mesh/QuadMesh.h"
#include "stb_image.h"
#include "../ayy/headers/Mesh/SkyBoxMesh.h"
#include "SkyBoxNode.h"

static const int kBoxCount = 7;
static const int kBoxPosClamp = 5;
static const int kWindowsCount = 20;

static const ayy::Vec3f kCameraDefaultPos(0,0,-7);
static const float kBorderScale = 1.1f;

static const char* items[] = { "InverseColor", "Gray", "Sharpen","Blur","Edge","Origin" };

Lesson17::Lesson17(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
}

Lesson17::~Lesson17()
{

}

void Lesson17::Prepare()
{
//    _frameBuffer = new ayy::AYYFrameBuffer(GetViewportWidth(),GetViewportHeight());
    
    // meshes
    _boxMesh = new ayy::BoxUVNormMesh();
    _boxMesh->Prepare();
    
    _planeMesh = new ayy::PlaneUVMesh();
    _planeMesh->Prepare();
    
    _quadMesh = new ayy::QuadMesh();
    _quadMesh->Prepare();
    
    _skyBoxMesh = new ayy::SkyBoxMesh();
    _skyBoxMesh->Prepare();
    
    // textures
    Prepare2DTexture();
    PrepareCubeTexture();
    
    // shaders
    _boxShader = ayy::Util::CreateShaderWithFile("res/lesson15_box.vs","res/lesson15_box.fs");
    _planeShader = ayy::Util::CreateShaderWithFile("res/lesson15_plane.vs","res/lesson15_plane.fs");
    _borderShader = ayy::Util::CreateShaderWithFile("res/lesson15_single_color.vs","res/lesson15_single_color.fs");
    _windowShader = ayy::Util::CreateShaderWithFile("res/lesson15_window.vs","res/lesson15_window.fs");
    _postProcessShader = ayy::Util::CreateShaderWithFile("res/lesson16_fbo.vs","res/lesson16_fbo.fs");
    _skyBoxShader = ayy::Util::CreateShaderWithFile("res/skybox.vs","res/skybox.fs");
    
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
    
    
    // post process node
    _postProcessNode = new Lesson16PostProcessNode();
    _postProcessNode->SetShader(_postProcessShader);
    _postProcessNode->SetMesh(_quadMesh);
    
    // skybox node
    _skyBoxNode = new SkyBoxNode();
    _skyBoxNode->SetShader(_skyBoxShader);
    _skyBoxNode->SetMesh(_skyBoxMesh);
    _skyBoxNode->SetTexture(_skyboxTexture);
}

void Lesson17::Cleanup()
{
    // clean specials
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_frameBuffer);
    
    // clean mesh
    _boxMesh->Cleanup();
    AYY_SAFE_DEL(_boxMesh);
    
    _planeMesh->Cleanup();
    AYY_SAFE_DEL(_planeMesh);
    
    _skyBoxMesh->Cleanup();
    AYY_SAFE_DEL(_skyBoxMesh);
    
    // clean shaders
    AYY_SAFE_DEL(_boxShader);
    AYY_SAFE_DEL(_planeShader);
    AYY_SAFE_DEL(_borderShader);
    AYY_SAFE_DEL(_windowShader);
    AYY_SAFE_DEL(_postProcessShader);
    AYY_SAFE_DEL(_skyBoxShader);
    
    // clean nodes
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
    AYY_SAFE_DEL(_postProcessNode);
    AYY_SAFE_DEL(_skyBoxNode);
   
}

void Lesson17::OnUpdate()
{
    // @miao @todo
    
}

void Lesson17::OnRender()
{
    if(_frameBuffer != nullptr)
    {
        _frameBuffer->Bind();
    }

    DrawScene();
    
    if(_frameBuffer != nullptr)
    {
        _frameBuffer->UnBind();
    }
    
    DrawPostProcess();
}

void Lesson17::DrawScene()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // draw sky box
    _skyBoxNode->OnRender(_camera);
    
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

void Lesson17::DrawPostProcess()
{
    if(_frameBuffer != nullptr)
    {
        ayy::TextureManager::GetInstance()->BindTextureToSlot(_frameBuffer->GetTextureUUID(),0);
        _postProcessNode->OnRender(_camera);
    }
}

void Lesson17::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
    
    
    // @miao @todo
    // 这里好像还是有问题。。。  render texture 好像大小 不适配 ，会有问题..
    AYY_SAFE_DEL(_frameBuffer);
//    _frameBuffer = new ayy::AYYFrameBuffer(GetViewportWidth(),GetViewportHeight());
}

void Lesson17::Prepare2DTexture()
{
    _boxTexture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/box_diffuse.png");
    _boxTexture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/emoji_wa.png");
    _planeTexture = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/marble.jpg");
    _windowTexture = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/blending_transparent_window.png");
}

void Lesson17::PrepareCubeTexture()
{
    _skyboxTexture = ayy::TextureManager::GetInstance()->CreateCubeTexture("res/skybox/right.jpg",
                                                                           "res/skybox/left.jpg",
                                                                           "res/skybox/top.jpg",
                                                                           "res/skybox/bottom.jpg",
                                                                           "res/skybox/back.jpg",
                                                                           "res/skybox/front.jpg");
}

void Lesson17::HandleKeyboardInput(GLFWwindow* window)
{
    static ayy::AYYFrameBuffer* holdBuffer = nullptr;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        AYY_SAFE_DEL(_frameBuffer);
        
        if(holdBuffer != nullptr)
        {
            _frameBuffer = holdBuffer;
            holdBuffer = nullptr;
        }
        else
        {
            holdBuffer = _frameBuffer;
            _frameBuffer = nullptr;
        }

    }

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

void Lesson17::OnGUI()
{
    BaseScene::OnGUI();
    
    if(ImGui::Combo("postprocessing", &_selectPostProcess, items, IM_ARRAYSIZE(items)))
    {
        _postProcessNode->postProcessIndex = _selectPostProcess;
    }
}
