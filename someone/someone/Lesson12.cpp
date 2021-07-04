#include "Lesson12.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Batch/TestBatch.h"
#include "../ayy/headers/Batch/PlaneBatch.h"
#include "../ayy/headers/Batch/BoxBatch.h"
#include "Node/CommonNode.h"
#include "../ayy/headers/Common.h"
#include "PhongMatNode.h"
//#include "../ayy/headers/Batch/BoxNormalBatch.h"
#include "AyyImGUI.h"
#include "../ayy/headers/Batch/BoxUVNormBatch.h"

Lesson12::Lesson12(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    _groundBatch = new ayy::PlaneBatch();
    _boxBatch = new ayy::BoxBatch();
    _objBatch = new ayy::BoxUVNormBatch();
    
    _ground = new CommonNode();
    _dummyLight = new CommonNode();
    _obj = new PhongMatNode();
    
//    _curLightPos = ayy::Vec3f(1,2,-3);
    
    _lightAmbient = ayy::Vec3f(0.2f,0.2f,0.2f);
    _lightDiffuse = ayy::Vec3f(0.5f,0.5f,0.5f);
    _lightSpecular = ayy::Vec3f(1.0f,1.0f,1.0f);
    
    _objAmbient = ayy::Vec3f(1.0f,0.5f,0.31f);
    _objDiffuse = ayy::Vec3f(1.0f,0.5f,0.31f);
    _objSpecular = ayy::Vec3f(0.5f,0.5f,0.5f);
    _objShininess = 32.0f;
}

Lesson12::~Lesson12()
{
    AYY_SAFE_DEL(_groundBatch);
    AYY_SAFE_DEL(_boxBatch);
    AYY_SAFE_DEL(_objBatch);
    AYY_SAFE_DEL(_dummyLight);
    AYY_SAFE_DEL(_obj);
}

void Lesson12::Prepare()
{
    // res
    _groundShader = ayy::Util::CreateShaderWithFile("res/ground_plane.vs","res/ground_plane.fs");
    _dummyLightShader = ayy::Util::CreateShaderWithFile("res/dummy_light.vs","res/dummy_light.fs");
    _phongShader = ayy::Util::CreateShaderWithFile("res/phong_mat.vs","res/phong_mat.fs");
    
    _groundBatch->Prepare();
    _boxBatch->Prepare();
    _objBatch->Prepare();
    
    PrepareTexture();
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,0,-7));
    
    // ground
    _ground->SetBatch(_groundBatch);
    _ground->SetShader(_groundShader);
    _ground->SetPosition(-10,-2,-10);
    _ground->SetScale(20);
    
    // dummy light
    _dummyLight->SetBatch(_boxBatch);
    _dummyLight->SetShader(_dummyLightShader);
//    _dummyLight->SetPosition(_curLightPos);
    _dummyLight->SetScale(1.0f);
    
    // be light box
    _obj->SetBatch(_objBatch);
    _obj->SetShader(_phongShader);
    _obj->SetPosition(0,0,0);
    _obj->SetRotAxis(ayy::Vec3f(0,1,0));
    _obj->SetRotation(45);
    _obj->SetScale(_objCurScale);
    
    _obj->SetLightSourcePos(_dummyLight->GetPosition());
    _obj->SetViewPos(_camera->GetPos());
    _obj->SetMaterial(_objAmbient,_objDiffuse,_objSpecular,_objShininess);
    _obj->SetLight(_lightAmbient,_lightDiffuse,_lightSpecular);
}

void Lesson12::Cleanup()
{
    AYY_SAFE_DEL(_groundShader);
    AYY_SAFE_DEL(_dummyLightShader);
    AYY_SAFE_DEL(_phongShader);
    _boxBatch->Cleanup();
    _objBatch->Cleanup();
    _groundBatch->Cleanup();
    AYY_SAFE_DEL(_camera);
}

void Lesson12::OnUpdate()
{
    // light pos
    {
        ayy::Mat4x4f trans,rot;
        ayy::MakeTranslateMatrix(trans,4,-0.5,0);
        ayy::MakeRotateByYMatrix(rot,ayy::DegToRad(_curLightDeg));
        _curLightDeg += GetDeltaTime() * _lightRotSpeed;
        
        // dummy light
        ayy::Vec4f tempPos = ayy::Vec4f(0,0,0,1) * trans * rot;
        _dummyLight->SetPosition(tempPos.x(),tempPos.y(),tempPos.z());
    }
    
    // obj
    {
        _obj->SetScale(_objCurScale);
        // obj light info
        _obj->SetLightSourcePos(_dummyLight->GetPosition());
        _obj->SetViewPos(_camera->GetPos());
        
        // obj material
        _obj->SetMaterial(_objAmbient,_objDiffuse,_objSpecular,_objShininess);
        
        // light color
        _obj->SetLight(_lightAmbient,_lightDiffuse,_lightSpecular);
    }

}

void Lesson12::OnRender()
{
    _ground->OnRender(_camera);
    _dummyLight->OnRender(_camera);
    _obj->OnRender(_camera);
}

void Lesson12::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

void Lesson12::PrepareTexture()
{

}

void Lesson12::HandleKeyboardInput(GLFWwindow* window)
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

void Lesson12::OnGUI()
{
    BaseScene::OnGUI();
        
    ImGui::Begin("Light Panel");
    ImGui::ColorEdit3("light ambient",_lightAmbient.data);
    ImGui::ColorEdit3("light diffuse",_lightDiffuse.data);
    ImGui::ColorEdit3("light specular",_lightSpecular.data);
    ImGui::SliderFloat("light rot speed",&_lightRotSpeed,0.0f,360.0f);
    ImGui::End();
    
    ImGui::Begin("Obj Material Panel");
    ImGui::ColorEdit3("obj ambient",_objAmbient.data);
    ImGui::ColorEdit3("obj diffuse",_objDiffuse.data);
    ImGui::ColorEdit3("obj specular",_objSpecular.data);
    ImGui::SliderFloat("obj shiness",&_objShininess,0.0f,128.0f);
    ImGui::SliderFloat("obj scale",&_objCurScale,0.5f,2.5f);
    ImGui::End();
}
