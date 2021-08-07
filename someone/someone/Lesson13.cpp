#include "Lesson13.h"
#include "PhongMultLightNode.h"
#include "PhongMultiLightMaterial.h"

static const int kBoxCount = 7;
static const int kBoxPosClamp = 5;


Lesson13::Lesson13(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    _boxBatch = new ayy::BoxMesh();
    _objBatch = new ayy::BoxUVNormMesh();
    _dummyLight = new ayy::CommonNode();
    
    for(int i = 0;i < kBoxCount;i++)
    {
        _boxes.push_back(new PhongMultLightNode());
    }
    
    _objShininess = 32.0f;
    
    _dirLightParam.direction = ayy::Vec3f(-1,-6,9);
}

Lesson13::~Lesson13()
{
    AYY_SAFE_DEL(_boxBatch);
    AYY_SAFE_DEL(_objBatch);
    AYY_SAFE_DEL(_dummyLight);
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        PhongMultLightNode* box = *it;
        AYY_SAFE_DEL(box);
    }
    _boxes.clear();
}

void Lesson13::Prepare()
{
    // res
    _dummyLightShader = ayy::Util::CreateShaderWithFile("res/dummy_light.vs","res/dummy_light.fs");
    _phongShader = ayy::Util::CreateShaderWithFile("res/phong_mul_light_src.vs","res/phong_mul_light_src.fs");
    
    _boxBatch->Prepare();
    _objBatch->Prepare();
    
    PrepareTexture();
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,0,-7));
    
    // dummy light
    _dummyLight->SetMesh(_boxBatch);
    _dummyLight->SetShader(_dummyLightShader);
    _dummyLight->SetScale(1.0f);
    
    // be light box
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        PhongMultLightNode* box = *it;
        
        int x = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        int y = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        int z = ayy::Util::Rand(-kBoxPosClamp,kBoxPosClamp);
        
        float rx = (float)ayy::Util::Rand(-10,10) / 10.0f;
        float ry = (float)ayy::Util::Rand(-10,10) / 10.0f;
        float rz = (float)ayy::Util::Rand(-10,10) / 10.0f;
        
        float rotAngle = ayy::Util::Rand(-180,180);
        box->SetRotAxis(ayy::Vec3f(rx,ry,rz));
        
        // random
        box->SetMesh(_objBatch);
        box->SetShader(_phongShader);
        box->SetPosition(x,y,z);
        box->SetRotation(rotAngle);
        box->SetScale(_objCurScale);
        
//        box->SetLight(_lightAmbient,_lightDiffuse,_lightSpecular);
        
        // material 
        PhongMultiLightMaterial* mat = box->GetMaterial();
        mat->SetTexture(_texDiffuse,_texSpecular);
        mat->SetSpecularShininess(_objShininess);
        
        // light
        mat->SetDirectionLightParam(_dirLightParam);
        mat->SetPosLightParam(_pointLightParam);
        mat->SetSpotLightParam(_spotLightParam);
        
        mat->SetViewPos(_camera->GetPos());
    }
}

void Lesson13::Cleanup()
{
    AYY_SAFE_DEL(_dummyLightShader);
    AYY_SAFE_DEL(_phongShader);
    _boxBatch->Cleanup();
    _objBatch->Cleanup();
    AYY_SAFE_DEL(_camera);
}

void Lesson13::OnUpdate()
{
    glClearColor(_dirLightParam.ambient.data[0],
                 _dirLightParam.ambient.data[1],
                 _dirLightParam.ambient.data[2],
                 1.0f);
    
    // dummy light
    _dummyLight->SetPosition(_pointLightPos.x(),_pointLightPos.y(),_pointLightPos.z());
    
    // point light
    _pointLightParam.position = _dummyLight->GetPosition();
    
    // spot light
    _spotLightParam.position = _camera->GetPos();
    _spotLightParam.direction = _camera->GetLookDir();
    
    // boxes
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        PhongMultLightNode* box = *it;
        box->SetScale(_objCurScale);
        
        // obj light info
        PhongMultiLightMaterial* mat = box->GetMaterial();
        mat->SetSpecularShininess(_objShininess);
        
        // light info
        mat->SetDirectionLightParam(_dirLightParam);
        mat->SetPosLightParam(_pointLightParam);
        mat->SetSpotLightParam(_spotLightParam);
        
        // light switchers
        mat->SetDirLightEnable(_bEnableDirLight);
        mat->SetPointLightEnable(_bEnablePointLight);
        mat->SetSpotLightEnable(_bEnableSpotLight);
        
        // view pos
        mat->SetViewPos(_camera->GetPos());
    }
}

void Lesson13::OnRender()
{
    _dummyLight->OnRender(_camera);
    for(auto it = _boxes.begin();it != _boxes.end();it++)
    {
        PhongMultLightNode* box = *it;
        box->OnRender(_camera);
    }
}

void Lesson13::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

void Lesson13::PrepareTexture()
{
    _texDiffuse = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/box_diffuse.png");
    _texSpecular = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/box_specular.png");
}

void Lesson13::HandleKeyboardInput(GLFWwindow* window)
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

void Lesson13::OnGUI()
{
    BaseScene::OnGUI();
        

    ImGui::Begin("Light Panel");
    {
        ImGui::Checkbox("dir light enable",&_bEnableDirLight);
        ImGui::Checkbox("point light enable",&_bEnablePointLight);
        ImGui::Checkbox("spot light enable",&_bEnableSpotLight);
        
        ImGui::LabelText("dirLight","dir light property");
        ImGui::DragFloat3("dirLight.dir",_dirLightParam.direction.data);
        ImGui::ColorEdit3("dirLight.ambient",_dirLightParam.ambient.data);
        ImGui::ColorEdit3("dirLight.diffuse",_dirLightParam.diffuse.data);
        ImGui::ColorEdit3("dirLight.specular",_dirLightParam.specular.data);
        
        ImGui::LabelText("pointLight","point light property");
//        ImGui::SliderFloat("light rot speed",&_lightRotSpeed,0.0f,360.0f);
        
        ImGui::SliderFloat("point light x",&_pointLightPos.data[0],-5.0f,5.0f);
        ImGui::SliderFloat("point light y",&_pointLightPos.data[1],-5.0f,5.0f);
        ImGui::SliderFloat("point light z",&_pointLightPos.data[2],-5.0f,5.0f);
        
        
        ImGui::ColorEdit3("pointLight.ambient",_pointLightParam.ambient.data);
        ImGui::ColorEdit3("pointLight.diffuse",_pointLightParam.diffuse.data);
        ImGui::ColorEdit3("pointLight.specular",_pointLightParam.specular.data);
        ImGui::SliderFloat("pointLight.constant",&_pointLightParam.constant,1.0f,3.0f);
        ImGui::SliderFloat("pointLight.linear",&_pointLightParam.linear,0.0f,1.0f);
        ImGui::SliderFloat("pointLight.quadratic",&_pointLightParam.quadratic,0.0f,2.0f);
        
        
        ImGui::LabelText("spotLight","spot light property");
        ImGui::SliderFloat("spotLight inner angle",&_spotLightParam.deg,0.f,45.0f);
        ImGui::SliderFloat("spotLight outer angle",&_spotLightParam.outerDeg,0.f,45.0f);
        
        ImGui::ColorEdit3("spotLight.ambient",_spotLightParam.ambient.data);
        ImGui::ColorEdit3("spotLight.diffuse",_spotLightParam.diffuse.data);
        ImGui::ColorEdit3("spotLight.specular",_spotLightParam.specular.data);
    }
    ImGui::End();

    
    ImGui::Begin("Obj Material Panel");
    ImGui::SliderFloat("obj shiness",&_objShininess,0.0f,128.0f);
    ImGui::SliderFloat("obj scale",&_objCurScale,0.5f,2.5f);
    ImGui::End();
}
