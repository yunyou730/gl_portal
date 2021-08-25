#include "Lesson21.h"
#include "LessonSpecialNodes.h"
#include "SkyBoxNode.h"

#include <ft2build.h>
#include FT_FREETYPE_H

static const ayy::Vec3f kCameraDefaultPos(0,0,15);
static const ayy::Vec3f kDummyLightInitPos(7,0,0);
static const float kDummyLightRotSpeed = 50.0f;

static bool s_bEnableNormalMap = true;
static bool s_bLightRun = true;

static float wallScale = 10.0;

Lesson21::Lesson21(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
}

Lesson21::~Lesson21()
{

}

void Lesson21::Prepare()
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
    PrepareFont();
    
    // shaders
    _planeShader = ayy::Util::CreateShaderWithFile("res/lesson15_plane.vs","res/lesson15_plane.fs");
    _skyBoxShader = ayy::Util::CreateShaderWithFile("res/skybox.vs","res/skybox.fs");
    _wallShader = ayy::Util::CreateShaderWithFile("res/lesson21_test.vs","res/lesson21_test.fs");
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
    _glyphNode = new Lesson21TestSDF();
    _glyphNode->SetShader(_wallShader);
    _glyphNode->SetMesh(_quadMesh);
    _glyphNode->SetScale(ayy::Vec3f(wallScale,wallScale,wallScale));
    _glyphNode->SetRotAxis(ayy::Vec3f(1,1,1));
//    _glyphNode->SetRotation(45);
    
    // dummy light
    _dummyLightNode = new ayy::CommonNode();
    _dummyLightNode->SetMesh(_boxMesh);
    _dummyLightNode->SetShader(_dummyLightShader);
    _dummyLightNode->SetPosition(kDummyLightInitPos);
}

void Lesson21::Cleanup()
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
    AYY_SAFE_DEL(_glyphNode);
    AYY_SAFE_DEL(_dummyLightNode);
}

void Lesson21::OnUpdate()
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
    
    
    _glyphNode->SetScale(ayy::Vec3f(wallScale,wallScale,wallScale));
}

void Lesson21::OnRender()
{
    // draw to frame buffer
    DrawScene();
    // present framebuffer
    DrawPostProcess();
}

void Lesson21::DrawScene()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_planeTexture,0); // to be check...
    // draw wall

    Character& ch = _characters.find('s')->second;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,ch.TextureID);
    
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_wallNormalMap,1);
    _glyphNode->OnRender(_camera);
        
    // draw dummy light
//    _dummyLightNode->OnRender(_camera);
}

void Lesson21::DrawPostProcess()
{

}

void Lesson21::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

void Lesson21::Prepare2DTexture()
{
    _planeTexture = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/marble.jpg");
    _wallDiffuse = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/brickwall.jpg");
    _wallNormalMap = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/brickwall_normal.jpg");
}

void Lesson21::PrepareCubeTexture()
{
    _skyboxTexture = ayy::TextureManager::GetInstance()->CreateCubeTexture("res/skybox/right.jpg",
                                                                           "res/skybox/left.jpg",
                                                                           "res/skybox/top.jpg",
                                                                           "res/skybox/bottom.jpg",
                                                                           "res/skybox/back.jpg",
                                                                           "res/skybox/front.jpg");
}

void Lesson21::PrepareFont()
{
    // @miao @todo
    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        printf("ERROR::FREETYPE: Could not init FreeType Library\n");
        return;
    }
    
    FT_Face face;
    if(FT_New_Face(ft, "res/xinqingnian.ttf", 0, &face))
    {
        printf("ERROR::FREETYPE: Failed to load font");
        return;
    }
    
    FT_Set_Pixel_Sizes(face,0,48);
    
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    
    
    // @miao @todo
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
    for (GLubyte c = 0; c < 128; c++)
    {
        // 加载字符的字形
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        
        // 生成纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 储存字符供之后使用
        Character character = {
            texture,
            ayy::Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            ayy::Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint)face->glyph->advance.x
        };
        _characters.insert(std::pair<GLchar, Character>(c, character));
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Lesson21::HandleKeyboardInput(GLFWwindow* window)
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
    
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        
    }
}

void Lesson21::OnGUI()
{
    BaseScene::OnGUI();
    
    ImGui::DragFloat("node scale",&wallScale,0.05,0.1,10.0);
    
}
