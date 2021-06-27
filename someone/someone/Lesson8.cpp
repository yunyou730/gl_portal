#include "Lesson8.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Batch/TestBatch.h"
#include "../ayy/headers/Batch/PlaneBatch.h"


Lesson8::Lesson8(int viewportWidth,int viewportHeight)
    :LessonBase(viewportWidth,viewportHeight)
{
    _batch = new ayy::TestBatch();
    _groundBatch = new ayy::PlaneBatch();
}

Lesson8::~Lesson8()
{
    if(_batch != nullptr)
    {
        delete _batch;
        _batch = nullptr;
    }
    
    if(_groundBatch != nullptr)
    {
        delete _groundBatch;
        _groundBatch = nullptr;
    }
}

void Lesson8::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/mvp_test_2.vs","res/mvp_test_2.fs");
    _box2Shader = ayy::Util::CreateShaderWithFile("res/mvp_test_2.vs","res/mvp_test_2.fs");
    _groundShader = ayy::Util::CreateShaderWithFile("res/ground_plane.vs","res/ground_plane.fs");
    
    _batch->Prepare();
//    _box2Batch->Prepare();
    _groundBatch->Prepare();
    
    PrepareTexture();
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
}

void Lesson8::Cleanup()
{
    if(_shader != nullptr)
    {
        delete _shader;
        _shader = nullptr;
    }
    
    if(_groundShader != nullptr)
    {
        delete _groundShader;
        _groundShader = nullptr;
    }
    
    _batch->Cleanup();
    _groundBatch->Cleanup();
    
    if(_camera != nullptr)
    {
        delete _camera;
        _camera = nullptr;
    }
}

void Lesson8::OnRender(float deltaTime)
{
    // draw box
    {
        // using shader
        _shader->Use();
        
        // using texture
        ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture1,0);
        ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture2,1);
        _shader->SetUniform("texture1",0);      // texture1 使用 GL_TEXTURE0 slot
        _shader->SetUniform("texture2",1);      // texture2 使用 GL_TEXTURE1 slot
        
        UpdateTransformBox(deltaTime);
        
        // box batch
        _batch->Bind();
        _batch->Draw();
        _batch->UnBind();
        
        _shader->UnUse();
    }
    
    // box2
    {
        _box2Shader->Use();
        
        // using texture
        ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture1,0);
        ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture2,1);
        _box2Shader->SetUniform("texture1",0);      // texture1 使用 GL_TEXTURE0 slot
        _box2Shader->SetUniform("texture2",1);      // texture2 使用 GL_TEXTURE1 slot
        
        UpdateTransformBox2(deltaTime);
        
        // box2 batch
        _batch->Bind();
        _batch->Draw();
        _batch->UnBind();
        
        _box2Shader->UnUse();
    }
    
    // draw plane
    {
        _groundShader->Use();
        
        UpdateTransformGround(deltaTime);
        
        _groundBatch->Bind();
        _groundBatch->Draw();
        _groundBatch->UnBind();
        
        _groundShader->UnUse();
    }
    
    
    // dump
    ayy::Vec3f look = _camera->GetLookDir();
    printf("camera look");
    look.Dump();
    
    
    ayy::Vec3f left = _camera->GetLeftDir();
    printf("left dir");
    left.Dump();
    
    ayy::Vec3f up = _camera->GetUpDir();
    
    float dot = left.Dot(look);
    printf("left dot look:%.5f\n",dot);
    
    dot = up.Dot(look);
    printf("up dot look:%.5f\n",dot);
    
    dot = up.Dot(left);
    printf("up dot left:%.5f\n",dot);
    
}

void Lesson8::PrepareTexture()
{
    _texture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/container.jpg");
    _texture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/awesomeface.png");
}

void Lesson8::UpdateTransformBox(float deltaTime)
{
    ayy::Vec3f pos(1,1,1);
    ayy::Vec3f axis(1,1,0);
    
    axis.Normalize();
    _box1Rot += deltaTime * _rotSpeed;
    
    
    ayy::Mat4x4f matScale;
    ayy::Mat4x4f matTranslate;
    ayy::Mat4x4f matRot;

    
//    matTranslate.Identify();
    ayy::MakeTranslateMatrix(matTranslate,1,0,1);
    matScale.Identify();
    
    ayy::MakeRotateByAxisMatrix(matRot,axis,ayy::DegToRad(_box1Rot));
    
    
    
//     mvp
    ayy::Mat4x4f matModel = matScale * matRot * matTranslate;
    ayy::Mat4x4f matMVP = matModel * _camera->GetViewMatrix() * _camera->GetProjMatrix();
    _shader->SetUniformMat4x4("uMVP",(GLfloat*)matMVP.data);
}

void Lesson8::UpdateTransformBox2(float deltaTime)
{
    ayy::Mat4x4f matScale;
    ayy::Mat4x4f matTranslate;
    ayy::Mat4x4f matRot,matRotateByX,matRotateByY,matRotateByZ;
    
    ayy::MakeTranslateMatrix(matTranslate,0,1,-4);
    ayy::MakeScaleMatrix(matScale,1.0f);
    
    ayy::MakeRotateByXMatrix(matRotateByX,ayy::DegToRad(_rot.x()));
    ayy::MakeRotateByYMatrix(matRotateByY,ayy::DegToRad(_rot.y()));
    ayy::MakeRotateByZMatrix(matRotateByZ,ayy::DegToRad(_rot.z()));
    matRot = matRotateByX * matRotateByY * matRotateByZ;
    
//     mvp
    ayy::Mat4x4f matModel = matScale * matRot * matTranslate;
    ayy::Mat4x4f matMVP = matModel * _camera->GetViewMatrix() * _camera->GetProjMatrix();
    _box2Shader->SetUniformMat4x4("uMVP",(GLfloat*)matMVP.data);
}

void Lesson8::UpdateTransformGround(float deltaTime)
{
    ayy::Mat4x4f matModel;
    
    ayy::Mat4x4f matScale,matTrans;
    ayy::MakeScaleMatrix(matScale,20.0f);
    ayy::MakeTranslateMatrix(matTrans,-10,-1,-10);
    
    matModel = matScale * matTrans;
    
    _groundShader->SetUniformMat4x4("u_Model",(GLfloat*)matModel.data);
    _groundShader->SetUniformMat4x4("u_View",(GLfloat*)_camera->GetViewMatrix().data);
    _groundShader->SetUniformMat4x4("u_Projection",(GLfloat*)_camera->GetProjMatrix().data);
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
        ayy::Vec3f deltaVec = delta * _camera->GetLeftDir();
        _camera->TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        ayy::Vec3f deltaVec = -delta * _camera->GetLeftDir();
        _camera->TakeMove(deltaVec.x(),deltaVec.y(),deltaVec.z());
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        _camera->TakeRoll(deltaRot);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        _camera->TakeRoll(-deltaRot);
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
