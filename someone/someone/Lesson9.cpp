#include "Lesson9.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Batch/TestBatch.h"
#include "../ayy/headers/Batch/PlaneBatch.h"
#include "../ayy/headers/Batch/BoxBatch.h"
#include "Node/CommonNode.h"
#include "../ayy/headers/Common.h"
#include "PhongNode.h"


const static ayy::Vec3f kLightColor(1.0f,1.0f,1.0f);


Lesson9::Lesson9(int viewportWidth,int viewportHeight)
    :LessonBase(viewportWidth,viewportHeight)
{
    _batch = new ayy::TestBatch();
    _groundBatch = new ayy::PlaneBatch();
    _boxBatch = new ayy::BoxBatch();
    
    _box1 = new CommonNode();
    _box2 = new CommonNode();
    _ground = new CommonNode();
    _dummyLight = new CommonNode();
    _obj = new PhongNode();
}

Lesson9::~Lesson9()
{
    AYY_SAFE_DEL(_batch);
    AYY_SAFE_DEL(_groundBatch);
    AYY_SAFE_DEL(_boxBatch);
    AYY_SAFE_DEL(_box1);
    AYY_SAFE_DEL(_box2);
    AYY_SAFE_DEL(_dummyLight);
    AYY_SAFE_DEL(_obj);
}

void Lesson9::Prepare()
{
    // res
    _commonShader = ayy::Util::CreateShaderWithFile("res/common.vs","res/common.fs");
    _groundShader = ayy::Util::CreateShaderWithFile("res/ground_plane.vs","res/ground_plane.fs");
    _dummyLightShader = ayy::Util::CreateShaderWithFile("res/dummy_light.vs","res/dummy_light.fs");
    _phongShader = ayy::Util::CreateShaderWithFile("res/phong.vs","res/phong.fs");
    
    _batch->Prepare();
    _groundBatch->Prepare();
    _boxBatch->Prepare();
    
    PrepareTexture();
    
    // box1
    _box1->AddTex(_texture1);
    _box1->AddTex(_texture2);
    _box1->SetBatch(_batch);
    _box1->SetShader(_commonShader);
    _box1->SetRotAxis(ayy::Vec3f(1,1,1));
    _box1->SetPosition(0,0,3);
    
    // box2
    _box2->AddTex(_texture1);
    _box2->AddTex(_texture2);
    _box2->SetBatch(_batch);
    _box2->SetShader(_commonShader);
    _box2->SetRotAxis(ayy::Vec3f(0,1,0));
    _box2->SetPosition(0,1,-8);
    
    // ground
    _ground->SetBatch(_groundBatch);
    _ground->SetShader(_groundShader);
    _ground->SetPosition(-10,-2,-10);
    _ground->SetScale(20);
    
    // dummy light
    _dummyLight->SetBatch(_boxBatch);
    _dummyLight->SetShader(_dummyLightShader);
    _dummyLight->SetPosition(0,2,0);
    _dummyLight->SetScale(1.0f);
    
    // be light box
    _obj->SetBatch(_boxBatch);
    _obj->SetShader(_phongShader);  // @miao @todo
    _obj->SetPosition(0,0,0);
    
    _obj->SetLightColor(kLightColor);
    _obj->SetLightSourcePos(_dummyLight->GetPosition());
    _obj->SetObjectColor(ayy::Vec3f(1.0f, 0.5f, 0.31f));
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,0,-7));
}

void Lesson9::Cleanup()
{
    AYY_SAFE_DEL(_commonShader);
    AYY_SAFE_DEL(_groundShader);
    AYY_SAFE_DEL(_dummyLightShader);
    AYY_SAFE_DEL(_phongShader);
    _batch->Cleanup();
    _groundBatch->Cleanup();
    AYY_SAFE_DEL(_camera);
}

void Lesson9::OnUpdate()
{
    _box1->SetRotation(_box1->GetRotation() + GetDeltaTime() * _rotSpeed);
    
//    _box2->SetRotation(_box2->GetRotation() + GetDeltaTime() * _rotSpeed);

}

void Lesson9::OnRender(float deltaTime)
{
    _box1->OnRender(_camera);
    _box2->OnRender(_camera);
    _ground->OnRender(_camera);
    _dummyLight->OnRender(_camera);
    _obj->OnRender(_camera);
//    _camera->Dump();
}

void Lesson9::PrepareTexture()
{
    _texture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/container.jpg");
    _texture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/awesomeface.png");
}

void Lesson9::HandleKeyboardInput(GLFWwindow* window)
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
