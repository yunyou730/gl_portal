#include "Lesson8.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Mesh/TestMesh.h"
#include "../ayy/headers/Mesh/PlaneMesh.h"
#include "Node/CommonNode.h"
#include "../ayy/headers/Common.h"


Lesson8::Lesson8(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    _batch = new ayy::TestMesh();
    _groundBatch = new ayy::PlaneMesh();
    _box1 = new CommonNode();
    _box2 = new CommonNode();
    _ground = new CommonNode();
}

Lesson8::~Lesson8()
{
    AYY_SAFE_DEL(_batch);
    AYY_SAFE_DEL(_groundBatch);
    AYY_SAFE_DEL(_box1);
    AYY_SAFE_DEL(_box2);
}

void Lesson8::Prepare()
{
    // res
    _commonShader = ayy::Util::CreateShaderWithFile("res/common.vs","res/common.fs");
    _groundShader = ayy::Util::CreateShaderWithFile("res/ground_plane.vs","res/ground_plane.fs");
    
    _batch->Prepare();
    _groundBatch->Prepare();
        
    PrepareTexture();
    
    // box1
    _box1->AddTex(_texture1);
    _box1->AddTex(_texture2);
    _box1->SetBatch(_batch);
    _box1->SetShader(_commonShader);
    _box1->SetRotAxis(ayy::Vec3f(1,1,1));
    
    // box2
    _box2->AddTex(_texture1);
    _box2->AddTex(_texture2);
    _box2->SetBatch(_batch);
    _box2->SetShader(_commonShader);
    _box2->SetRotAxis(ayy::Vec3f(0,1,0));
    
    // ground
    _ground->SetBatch(_groundBatch);
    _ground->SetShader(_groundShader);
    _ground->SetPosition(-10,-2,-10);
    _ground->SetScale(20);
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,0,-7));
}

void Lesson8::Cleanup()
{
    AYY_SAFE_DEL(_commonShader);
    AYY_SAFE_DEL(_groundShader);
    _batch->Cleanup();
    _groundBatch->Cleanup();
    AYY_SAFE_DEL(_camera);
}

void Lesson8::OnUpdate()
{
    _box1->SetRotation(_box1->GetRotation() + GetDeltaTime() * _rotSpeed);
    _box1->SetPosition(0,0,0);
    
//    _box2->SetRotation(_box2->GetRotation() + GetDeltaTime() * _rotSpeed);
    _box2->SetPosition(0,1,-4);
}

void Lesson8::OnRender()
{
    _box1->OnRender(_camera);
    _box2->OnRender(_camera);
    _ground->OnRender(_camera);
//    _camera->Dump();
}

void Lesson8::PrepareTexture()
{
    _texture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/container.jpg");
    _texture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/awesomeface.png");
}

void Lesson8::HandleKeyboardInput(GLFWwindow* window)
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
    
    // box rotate
    delta = _rotSpeed * GetDeltaTime();
    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        _rot.SetZ(_rot.z() + delta);
    }
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        _rot.SetZ(_rot.z() - delta);
    }
    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        _rot.SetX(_rot.x() + delta);
    }
    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        _rot.SetX(_rot.x() - delta);
    }
    if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        _rot.SetY(_rot.y() + delta);
    }
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        _rot.SetY(_rot.y() - delta);
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
