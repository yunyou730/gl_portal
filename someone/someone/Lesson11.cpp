#include "Lesson11.h"
#include "PhongMatNode.h"

Lesson11::Lesson11(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    _batch = new ayy::TestMesh();
    _groundBatch = new ayy::PlaneMesh();
    _boxBatch = new ayy::BoxMesh();
    _boxNormalBatch = new ayy::BoxNormalMesh();
    
    _box1 = new ayy::CommonNode();
    _box2 = new ayy::CommonNode();
    _ground = new ayy::CommonNode();
    _dummyLight = new ayy::CommonNode();
    _obj = new PhongMatNode();
    
    _curLightPos = ayy::Vec3f(1,2,-3);
    
    _lightAmbient = ayy::Vec3f(0.2f,0.2f,0.2f);
    _lightDiffuse = ayy::Vec3f(0.5f,0.5f,0.5f);
    _lightSpecular = ayy::Vec3f(1.0f,1.0f,1.0f);
    
    _objAmbient = ayy::Vec3f(1.0f,0.5f,0.31f);
    _objDiffuse = ayy::Vec3f(1.0f,0.5f,0.31f);
    _objSpecular = ayy::Vec3f(0.5f,0.5f,0.5f);
    _objShininess = 32.0f;
}

Lesson11::~Lesson11()
{
    AYY_SAFE_DEL(_batch);
    AYY_SAFE_DEL(_groundBatch);
    AYY_SAFE_DEL(_boxBatch);
    AYY_SAFE_DEL(_boxNormalBatch);
    AYY_SAFE_DEL(_box1);
    AYY_SAFE_DEL(_box2);
    AYY_SAFE_DEL(_dummyLight);
    AYY_SAFE_DEL(_obj);
}

void Lesson11::Prepare()
{
    // res
    _commonShader = ayy::Util::CreateShaderWithFile("res/common.vs","res/common.fs");
    _groundShader = ayy::Util::CreateShaderWithFile("res/ground_plane.vs","res/ground_plane.fs");
    _dummyLightShader = ayy::Util::CreateShaderWithFile("res/dummy_light.vs","res/dummy_light.fs");
    _phongShader = ayy::Util::CreateShaderWithFile("res/phong_mat.vs","res/phong_mat.fs");
    
    _batch->Prepare();
    _groundBatch->Prepare();
    _boxBatch->Prepare();
    _boxNormalBatch->Prepare();
    
    PrepareTexture();
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,0,-7));
    
    // box1
    _box1->AddTex(_texture1);
    _box1->AddTex(_texture2);
    _box1->SetMesh(_batch);
    _box1->SetShader(_commonShader);
    _box1->SetRotAxis(ayy::Vec3f(1,1,1));
    _box1->SetPosition(0,0,3);
    
    // box2
    _box2->AddTex(_texture1);
    _box2->AddTex(_texture2);
    _box2->SetMesh(_batch);
    _box2->SetShader(_commonShader);
    _box2->SetRotAxis(ayy::Vec3f(0,1,0));
    _box2->SetPosition(0,1,-8);
    
    // ground
    _ground->SetMesh(_groundBatch);
    _ground->SetShader(_groundShader);
    _ground->SetPosition(-10,-2,-10);
    _ground->SetScale(20);
    
    // dummy light
    _dummyLight->SetMesh(_boxBatch);
    _dummyLight->SetShader(_dummyLightShader);
    _dummyLight->SetPosition(_curLightPos);
    _dummyLight->SetScale(1.0f);
    
    // be light box
    _obj->SetMesh(_boxNormalBatch);
    _obj->SetShader(_phongShader);
    _obj->SetPosition(0,0,0);
    _obj->SetRotAxis(ayy::Vec3f(0,1,0));
    _obj->SetRotation(45);
    _obj->SetScale(2.0f);
    
    _obj->SetLightSourcePos(_dummyLight->GetPosition());
    _obj->SetViewPos(_camera->GetPos());
    _obj->SetMaterial(_objAmbient,_objDiffuse,_objSpecular,_objShininess);
    _obj->SetLight(_lightAmbient,_lightDiffuse,_lightSpecular);
}

void Lesson11::Cleanup()
{
    AYY_SAFE_DEL(_commonShader);
    AYY_SAFE_DEL(_groundShader);
    AYY_SAFE_DEL(_dummyLightShader);
    AYY_SAFE_DEL(_phongShader);
    _batch->Cleanup();
    _groundBatch->Cleanup();
    AYY_SAFE_DEL(_camera);
}

void Lesson11::OnUpdate()
{
    // box1 rotation
    _box1->SetRotation(_box1->GetRotation() + GetDeltaTime() * _rotSpeed);
    
    // light pos
    ayy::Mat4x4f trans,rot;
    ayy::MakeTranslateMatrix(trans,4,-0.5,0);
    ayy::MakeRotateByYMatrix(rot,ayy::DegToRad(_curLightDeg));
    
    _curLightDeg += GetDeltaTime() * _lightRotSpeed;
    
    ayy::Vec4f tempPos = ayy::Vec4f(0,0,0,1) * trans * rot;
    _curLightPos = ayy::Vec3f(tempPos.x(),tempPos.y(),tempPos.z());
    _dummyLight->SetPosition(_curLightPos);
    
    // obj light info
    _obj->SetLightSourcePos(_dummyLight->GetPosition());
    _obj->SetViewPos(_camera->GetPos());
    
    // obj material
    _obj->SetMaterial(_objAmbient,_objDiffuse,_objSpecular,_objShininess);
    
    // light color
    _obj->SetLight(_lightAmbient,_lightDiffuse,_lightSpecular);
}

void Lesson11::OnRender()
{
    _box1->OnRender(_camera);
    _box2->OnRender(_camera);
    _ground->OnRender(_camera);
    _dummyLight->OnRender(_camera);
    _obj->OnRender(_camera);
//    _camera->Dump();
}

void Lesson11::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

void Lesson11::PrepareTexture()
{
    _texture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/container.jpg");
    _texture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/awesomeface.png");
}

void Lesson11::HandleKeyboardInput(GLFWwindow* window)
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

void Lesson11::OnGUI()
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
    ImGui::SliderFloat("float",&_objShininess,0.0f,128.0f);
    ImGui::End();
}
