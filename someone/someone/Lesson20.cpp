#include "Lesson20.h"
#include "LessonSpecialNodes.h"
#include "SkyBoxNode.h"

static const ayy::Vec3f kCameraDefaultPos(0,0,7);
static const ayy::Vec3f kDummyLightInitPos(7,0,0);
static const float kDummyLightRotSpeed = 50.0f;

static bool s_bEnableNormalMap = true;
static bool s_bLightRun = true;

Lesson20::Lesson20(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
}

Lesson20::~Lesson20()
{

}

void Lesson20::Prepare()
{
    _planeMesh = new ayy::PlaneUVMesh();
    _planeMesh->Prepare();
    
    _quadMesh = new ayy::PlaneUVNormMesh();
    _quadMesh->Prepare();
    
    _skyBoxMesh = new ayy::SkyBoxMesh();
    _skyBoxMesh->Prepare();
        
    _boxMesh = new ayy::BoxMesh();
    _boxMesh->Prepare();
    
    // textures
    Prepare2DTexture();
    PrepareCubeTexture();
    
    // shaders
    _planeShader = ayy::Util::CreateShaderWithFile("res/lesson15_plane.vs","res/lesson15_plane.fs");
    _skyBoxShader = ayy::Util::CreateShaderWithFile("res/skybox.vs","res/skybox.fs");
    _wallShader = ayy::Util::CreateShaderWithFile("res/lesson20_normalmap.vs","res/lesson20_normalmap.fs");
    _dummyLightShader = ayy::Util::CreateShaderWithFile("res/dummy_light.vs","res/dummy_light.fs");
    
    // camera
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(kCameraDefaultPos);
    _camera->SetLookDir(ayy::Vec3f(0,0,-1));
    
    // skybox node
    _skyBoxNode = new SkyBoxNode();
    _skyBoxNode->SetShader(_skyBoxShader);
    _skyBoxNode->SetMesh(_skyBoxMesh);
    _skyBoxNode->SetTexture(_skyboxTexture);
    
    // wall node
    _wallNode = new Lesson20NormalMapNode();
    _wallNode->SetShader(_wallShader);
    _wallNode->SetMesh(_quadMesh);
    _wallNode->SetScale(ayy::Vec3f(3.0,3.0,3.0));
//    _wallNode->SetRotAxis(ayy::Vec3f(1,0,0));
    _wallNode->SetRotation(45);
    
    _wallNode->SetPointLightAmbient(ayy::Vec3f(1.0,1.0,1.0));
    _wallNode->SetPointLightDiffuse(ayy::Vec3f(1.0,1.0,1.0));
    _wallNode->SetPointLightSpecular(ayy::Vec3f(1.0,1.0,1.0));
    _wallNode->SetPointLightFactors(1.0,0.045,0.0075);
    
    
    // dummy light
    _dummyLightNode = new ayy::CommonNode();
    _dummyLightNode->SetMesh(_boxMesh);
    _dummyLightNode->SetShader(_dummyLightShader);
    _dummyLightNode->SetPosition(kDummyLightInitPos);
}

void Lesson20::Cleanup()
{
    // clean specials
    AYY_SAFE_DEL(_camera);
    
    // clean mesh
    _planeMesh->Cleanup();
    AYY_SAFE_DEL(_planeMesh);
    
    _skyBoxMesh->Cleanup();
    AYY_SAFE_DEL(_skyBoxMesh);
    
    _boxMesh->Cleanup();
    AYY_SAFE_DEL(_boxMesh);
    
    // clean shaders
    AYY_SAFE_DEL(_planeShader);
    AYY_SAFE_DEL(_skyBoxShader);
    AYY_SAFE_DEL(_wallShader);
    AYY_SAFE_DEL(_dummyLightShader);
    
    // clean nodes
    AYY_SAFE_DEL(_skyBoxNode);
    AYY_SAFE_DEL(_wallNode);
    AYY_SAFE_DEL(_dummyLightNode);
}

void Lesson20::OnUpdate()
{
    // light pos
    if(s_bLightRun)
    {
        float delta = kDummyLightRotSpeed * GetDeltaTime();
        ayy::Vec3f dir = _dummyLightNode->GetPosition();
        ayy::Vec4f dir4(dir.x(),dir.y(),dir.z(),1.0);
        ayy::Mat4x4f rotMat;
        ayy::MakeRotateByYMatrix(rotMat,ayy::DegToRad(delta));
        dir4 = dir4 * rotMat;
        _dummyLightNode->SetPosition(ayy::Vec3f(dir4.x(),dir4.y(),dir4.z()));
    }
    
    // sync light pos to wall
    _wallNode->SetPointLightPos(_dummyLightNode->GetPosition());
    _wallNode->SetNormalMapEnable(s_bEnableNormalMap);
}

void Lesson20::OnRender()
{
    // draw to frame buffer
    DrawScene();
    // present framebuffer
    DrawPostProcess();
}

void Lesson20::DrawScene()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // draw sky box
//    _skyBoxNode->OnRender(_camera);
    
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_planeTexture,0); // to be check...
    // draw wall
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_wallDiffuse,0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_wallNormalMap,1);
    _wallNode->OnRender(_camera);
        
    // draw dummy light
    _dummyLightNode->OnRender(_camera);
}

void Lesson20::DrawPostProcess()
{

}

void Lesson20::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

void Lesson20::Prepare2DTexture()
{
    _planeTexture = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/marble.jpg");
    _wallDiffuse = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/brickwall.jpg");
    _wallNormalMap = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/brickwall_normal.jpg");
}

void Lesson20::PrepareCubeTexture()
{
    _skyboxTexture = ayy::TextureManager::GetInstance()->CreateCubeTexture("res/skybox/right.jpg",
                                                                           "res/skybox/left.jpg",
                                                                           "res/skybox/top.jpg",
                                                                           "res/skybox/bottom.jpg",
                                                                           "res/skybox/back.jpg",
                                                                           "res/skybox/front.jpg");
}

void Lesson20::HandleKeyboardInput(GLFWwindow* window)
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
    
    // camera rotate
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
    
    if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        _camera->SetLookDir(ayy::Vec3f(1,1,0));
    }
}

void Lesson20::OnGUI()
{
    BaseScene::OnGUI();
    
    ImGui::Checkbox("light run",&s_bLightRun);
    ImGui::Checkbox("enable normal map",&s_bEnableNormalMap);
    ImGui::Checkbox("enable wrong normal",&_wallNode->_bEnableWrongNormalMap);
    
    ImGui::ColorEdit3("pointLight.ambient",_wallNode->_pointLightAmbient.data);
    ImGui::ColorEdit3("pointLight.diffuse",_wallNode->_pointLightDiffuse.data);
    ImGui::ColorEdit3("pointLight.specular",_wallNode->_pointLightSpecular.data);
}
