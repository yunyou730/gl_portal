#include "Crude4.h"
#include <sstream>
#include "../Demo/FreeCamera.h"
#include "../Demo/ecs/Util.h"

extern ayy::BaseApplication* g_app;

Crude4::Crude4(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
    ,kShadowWidth(1024)
    ,kShadowHeight(1024)
{
    
}

Crude4::~Crude4()
{
    
}

void Crude4::Prepare()
{
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
    
    PrepareGroundMesh();
    PrepareBoxMesh();
    PrepareShadowMap();
    
    _groundShader = ayy::Util::CreateShaderWithFile("res/crude1/ground.vs","res/crude1/ground.fs");
    _boxShader = ayy::Util::CreateShaderWithFile("res/crude1/box.vs","res/crude1/box.fs");
    _depthMapShader = ayy::Util::CreateShaderWithFile("res/crude1/simple_depth_map.vs","res/crude1/simple_depth_map.fs");
    _debugDepthBufferShader = ayy::Util::CreateShaderWithFile("res/crude1/debug_depth_buffer.vs","res/crude1/debug_depth_buffer.fs");
    
    // camera
    _camera = new crude::FreeCamera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,5,7));
    _camera->SetLookDir(ayy::Vec3f(0,0,0) - _camera->GetPos());
//    _camera->SetMode(ayy::Camera::ECamProjMode::ORTHO);
    
    // light
    _light = new ayy::Camera(kShadowWidth,kShadowHeight);
    
    _light->SetPos(ayy::Vec3f(-3.504, 3.024, -0.836));
    _light->SetLookDir(ayy::Vec3f(0.693,-0.528,0.491));
    
    _light->SetNear(0.1);
    _light->SetFar(30.0);
//    _light->SetFar(1000.0);
    
    _light->SetMode(ayy::Camera::ECamProjMode::ORTHO);
//    _light->SetMode(ayy::Camera::ECamProjMode::PERSPECTIVE);
    
    // objects
    _groundTransform.SetScale(ayy::Vec3f(10.0,10.0,1.0));
    _groundTransform.SetPos(ayy::Vec3f(0,0,0));
    _groundTransform.SetRot(ayy::Vec3f(ayy::PI * 0.5,0,0));
    
    for(int i = 0;i < 7;i++)
    {
        crude::TransformComponent transform;
        int x = crude::Util::random(-4,4);
        int y = crude::Util::random(0,3);
        int z = crude::Util::random(-4,4);
        transform.SetPos(ayy::Vec3f(x,y,z));
        _boxes.push_back(transform);
    }
}

void Crude4::PrepareGroundMesh()
{
    ayy::BuiltinMesh* builtinMesh = g_app->GetBuiltinMeshFactory()->GetBuiltinMesh("ayy/builtin/quad");
    _groundVAO = builtinMesh->vao;
}

void Crude4::PrepareBoxMesh()
{
    ayy::BuiltinMesh* builtinMesh = g_app->GetBuiltinMeshFactory()->GetBuiltinMesh("ayy/builtin/cube");
    _boxVAO = builtinMesh->vao;
}

void Crude4::PrepareShadowMap()
{
    // gen depth map
    glGenTextures(1,&_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_DEPTH_COMPONENT,
                     kShadowWidth,
                     kShadowHeight,
                     0,
                     GL_DEPTH_COMPONENT,
                     GL_FLOAT,
                     nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // gen depth buffer & depth map make relation
    glGenFramebuffers(1,&_depthFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _depthFBO);
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Crude4::Cleanup()
{
    glDeleteFramebuffers(1,&_depthFBO);
    glDeleteTextures(1,&_depthMap);
    
    AYY_SAFE_DEL(_groundShader);
    AYY_SAFE_DEL(_boxShader);
    AYY_SAFE_DEL(_depthMapShader);
    AYY_SAFE_DEL(_debugDepthBufferShader);
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_light);
}

void Crude4::OnRender()
{
    DrawShadowMap();
    DrawScene();
    
    // debug
    if(_bDebugDepthBuffer)
    {
        DrawDepthBuffer();
    }
}

void Crude4::DrawScene()
{
//    int viewportWidth = GetViewportWidth();
//    int viewportHeight = GetViewportHeight();
//    printf("[%d x %d]\n",viewportWidth,viewportHeight);
    glViewport(0,0,GetViewportWidth(),GetViewportHeight());
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawGround(_groundShader,_camera,_light);
    DrawBoxes(_boxShader,_camera,_light);
}

void Crude4::DrawShadowMap()
{
    glViewport(0,0,kShadowWidth,kShadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, _depthFBO);
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        DrawGround(_depthMapShader,_light,nullptr);
        DrawBoxes(_depthMapShader,_light,nullptr);
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Crude4::DrawGround(ayy::ShaderProgram* shader,ayy::Camera* camera,ayy::Camera* light)
{
    shader->Use();
    
    shader->SetUniformMat4x4("u_Model",(GLfloat*)_groundTransform.GetWorldMatrix()->data);
    shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    if(light != nullptr)
    {
        shader->SetUniformMat4x4("u_LightView",(GLfloat*)light->GetViewMatrix().data);
        shader->SetUniformMat4x4("u_LightProjection",(GLfloat*)light->GetProjMatrix().data);
        
        // shadow map @miao @todo
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_depthMap);
        shader->SetUniform("u_ShadowMap",0);
    }
    
    glBindVertexArray(_groundVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
    shader->UnUse();
}

void Crude4::DrawBoxes(ayy::ShaderProgram* shader,ayy::Camera* camera,ayy::Camera* light)
{
    shader->Use();
    
    shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    if(light != nullptr)
    {
        shader->SetUniformMat4x4("u_LightView",(GLfloat*)light->GetViewMatrix().data);
        shader->SetUniformMat4x4("u_LightProjection",(GLfloat*)light->GetProjMatrix().data);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_depthMap);
        shader->SetUniform("u_ShadowMap",0);
    }
    
    glBindVertexArray(_boxVAO);
    
    for(auto it : _boxes)
    {
        shader->SetUniformMat4x4("u_Model",(GLfloat*)it.GetWorldMatrix()->data);
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,(void*)0);
    }
    
    shader->UnUse();
}

void Crude4::DrawDepthBuffer()
{
    // @miao @todo
    // show depth onto
    _debugDepthBufferShader->Use();
    
        // shadow map @miao @todo
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_depthMap);
    _debugDepthBufferShader->SetUniform("u_ShadowMap",0);
    
    if(_light->GetMode() == ayy::Camera::ECamProjMode::PERSPECTIVE)
    {
        _debugDepthBufferShader->SetUniform("isPersp",1.0f);
        _debugDepthBufferShader->SetUniform("nearPlane",_light->GetNear());
        _debugDepthBufferShader->SetUniform("farPlane",_light->GetFar());
    }
    else if(_light->GetMode() == ayy::Camera::ECamProjMode::ORTHO)
    {
        _debugDepthBufferShader->SetUniform("isPersp",0.0f);
    }

    
    glBindVertexArray(_groundVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
    _debugDepthBufferShader->UnUse();
    
}

void Crude4::HandleKeyboardInput(GLFWwindow* window)
{
    _camera->HandleKeyboardInput(window,GetDeltaTime());
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        _camera->Dump();
    }

    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        _bDebugDepthBuffer = !_bDebugDepthBuffer;
    }
    
}

void Crude4::OnViewportSizeChanged(int width,int height)
{
    ayy::BaseScene::OnViewportSizeChanged(width,height);
    _camera->SetViewportSize(width,height);
}

