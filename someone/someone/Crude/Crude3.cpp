#include "Crude3.h"
#include <sstream>
#include "../Demo/FreeCamera.h"
#include "../Demo/ecs/Util.h"

Crude3::Crude3(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
    ,kShadowWidth(1024)
    ,kShadowHeight(1024)
{
    
}

Crude3::~Crude3()
{
    
}

void Crude3::Prepare()
{
    PrepareGroundMesh();
    PrepareBoxMesh();
    PrepareShadowMap();
    
    _groundShader = ayy::Util::CreateShaderWithFile("res/crude1/ground.vs","res/crude1/ground.fs");
    _boxShader = ayy::Util::CreateShaderWithFile("res/crude1/box.vs","res/crude1/box.fs");
    _depthMapShader = ayy::Util::CreateShaderWithFile("res/crude1/simple_depth_map.vs","res/crude1/simple_depth_map.fs");
    
    // camera
    _camera = new crude::FreeCamera(GetViewportWidth(),GetViewportHeight());
    _camera->SetPos(ayy::Vec3f(0,5,7));
    _camera->SetLookDir(ayy::Vec3f(0,0,0) - _camera->GetPos());
//    _camera->SetMode(ayy::Camera::ECamProjMode::ORTHO);
    
    
    // light
    _light = new ayy::Camera(kShadowWidth,kShadowHeight);
    _light->SetPos(ayy::Vec3f(0.263,10.473,-14.297));
    _light->SetLookDir(ayy::Vec3f(0.161,-0.520,0.839));
    
    _light->SetPos(ayy::Vec3f(-3.504, 3.024, -0.836));
    _light->SetLookDir(ayy::Vec3f(0.693,-0.528,0.491));
    
    _light->SetNear(0.2);
    _light->SetFar(100.0);
    
    _light->SetMode(ayy::Camera::ECamProjMode::ORTHO);
    
    // objects
    _groundTransform.SetScale(ayy::Vec3f(20.0,1.0,20.0));
    _groundTransform.SetPos(ayy::Vec3f(-5.0,0.0,-5.0));
    
    for(int i = 0;i < 5;i++)
    {
        crude::TransformComponent transform;
        int x = crude::Util::random(-4,4);
        int y = crude::Util::random(0,3);
        int z = crude::Util::random(-4,4);
        transform.SetPos(ayy::Vec3f(x,y,z));
        _boxes.push_back(transform);
    }
}

void Crude3::PrepareGroundMesh()
{
    // vertices data
    float vertices[] = {
        // pos x3, uv x2
         0.0, 0.0, 0.0,  0.0,0.0,
         0.0, 0.0, 1.0,  0.0,1.0,
         1.0, 0.0, 0.0,  1.0,0.0,
         1.0, 0.0, 1.0,  1.0,1.0
    };
    
    // indice data
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
    };
    
    // VAO & VBO
    glGenVertexArrays(1,&_groundVAO);
    glGenBuffers(1,&_groundVBO);
    glGenBuffers(1,&_groundEBO);
    
    glBindVertexArray(_groundVAO);
    {
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER,_groundVBO);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1, uv
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_groundEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    
    // unbind VAO
    glBindVertexArray(0);
}

void Crude3::PrepareBoxMesh()
{
    // vertices
    float vertices[] = {
        
        0.0,0.0,0.0,
//         0.0f, 0.0f,
        0.0,1.0,0.0,
//         0.0f, 1.0f,
        1.0,0.0,0.0,
//         1.0f, 0.0f,
        1.0,1.0,0.0,
//         1.0f, 1.0f,
        
        0.0,0.0,1.0,
//         0.0f, 0.0f,
        0.0,1.0,1.0,
//         0.0f, 1.0f,
        1.0,0.0,1.0,
//         1.0f, 0.0f,
        1.0,1.0,1.0,
    };
    
    unsigned int indices[] = {
        0,1,2,
        2,1,3,
        
        4,5,6,
        6,5,7,
        
        4,5,0,
        0,5,1,
        
        2,3,6,
        6,3,7,
        
        3,1,7,
        7,1,5,
        
        4,0,6,
        6,0,2,
    };
    
    glGenVertexArrays(1,&_boxVAO);
    glGenBuffers(1,&_boxVBO);
    glGenBuffers(1,&_boxEBO);
    
    glBindVertexArray(_boxVAO);
    {
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER,_boxVBO);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_boxEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}

void Crude3::PrepareShadowMap()
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

void Crude3::Cleanup()
{
    glDeleteVertexArrays(1,&_groundVAO);
    glDeleteVertexArrays(1,&_boxVAO);
        
    glDeleteBuffers(1,&_groundVBO);
    glDeleteBuffers(1,&_groundEBO);
    glDeleteBuffers(1,&_boxVBO);
    glDeleteBuffers(1,&_boxEBO);
    
    glDeleteFramebuffers(1,&_depthFBO);
    glDeleteTextures(1,&_depthMap);
    
    AYY_SAFE_DEL(_groundShader);
    AYY_SAFE_DEL(_boxShader);
    AYY_SAFE_DEL(_depthMapShader);
    AYY_SAFE_DEL(_camera);
    AYY_SAFE_DEL(_light);
}

void Crude3::OnRender()
{
    DrawShadowMap();
    DrawScene();
}

void Crude3::DrawScene()
{
    glViewport(0,0,GetViewportWidth(),GetViewportHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawGround(_groundShader,_camera,_light);
    DrawBoxes(_boxShader,_camera,_light);
}

void Crude3::DrawShadowMap()
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

void Crude3::DrawGround(ayy::ShaderProgram* shader,ayy::Camera* camera,ayy::Camera* light)
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

void Crude3::DrawBoxes(ayy::ShaderProgram* shader,ayy::Camera* camera,ayy::Camera* light)
{
    shader->Use();
    
    shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    glBindVertexArray(_boxVAO);
    
    for(auto it : _boxes)
    {
        _boxShader->SetUniformMat4x4("u_Model",(GLfloat*)it.GetWorldMatrix()->data);
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,(void*)0);
    }
    
    shader->UnUse();
}

void Crude3::HandleKeyboardInput(GLFWwindow* window)
{
    _camera->HandleKeyboardInput(window,GetDeltaTime());
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        _camera->Dump();
    }
}
