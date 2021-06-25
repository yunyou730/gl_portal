#include "Lesson8.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"
#include "../ayy/headers/Batch/TestBatch.h"

Lesson8::Lesson8(int viewportWidth,int viewportHeight)
    :LessonBase(viewportWidth,viewportHeight)
{
    _batch = new ayy::TestBatch();
}

Lesson8::~Lesson8()
{
    if(_batch != nullptr)
    {
        delete _batch;
        _batch = nullptr;
    }
}

void Lesson8::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/mvp_test_2.vs","res/mvp_test_2.fs");
    _batch->Prepare();
    PrepareTexture();
    _camera = new ayy::Camera(GetViewportWidth(),GetViewportHeight());
}

void Lesson8::Cleanup()
{
    if(_shader != nullptr)
    {
        delete _shader;
    }
    _shader = nullptr;
    
    
    _batch->Cleanup();
    
    if(_camera != nullptr)
    {
        delete _camera;
    }
    _camera = nullptr;
}

void Lesson8::OnRender(float deltaTime)
{
    // using shader
    _shader->Use();
    
    // using texture
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture1,0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture2,1);
    _shader->SetUniform("texture1",0);      // texture1 使用 GL_TEXTURE0 slot
    _shader->SetUniform("texture2",1);      // texture2 使用 GL_TEXTURE1 slot
    
    UpdateTransform(deltaTime);
    
    // draw with VAO
    _batch->Bind();
    _batch->Draw();
    _batch->UnBind();
    _shader->UnUse();
}

void Lesson8::PrepareTexture()
{
    _texture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/container.jpg");
    _texture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/awesomeface.png");
}

void Lesson8::UpdateTransform(float deltaTime)
{
    ayy::Mat4x4f matScale;
    ayy::Mat4x4f matTranslate;
    ayy::Mat4x4f matRot,matRotateByX,matRotateByY,matRotateByZ;
    
    ayy::MakeTranslateMatrix(matTranslate,0.0f,0,0);
    ayy::MakeScaleMatrix(matScale,1.0f);
    
    ayy::MakeRotateByXMatrix(matRotateByX,ayy::DegToRad(_rot.x()));
    ayy::MakeRotateByYMatrix(matRotateByY,ayy::DegToRad(_rot.y()));
    ayy::MakeRotateByZMatrix(matRotateByZ,ayy::DegToRad(_rot.z()));
    matRot = matRotateByX * matRotateByY * matRotateByZ;
    
//     mvp
    ayy::Mat4x4f matModel = matScale * matRot * matTranslate;
    ayy::Mat4x4f matMVP = matModel * _camera->GetViewMatrix() * _camera->GetProjMatrix();
    _shader->SetUniformMat4x4("uMVP",(GLfloat*)matMVP.data);
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
        _camera->TakeRot(0,deltaRot,0);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera->TakeRot(0,-deltaRot,0);
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        _camera->TakeRot(deltaRot,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        _camera->TakeRot(-deltaRot,0,0);
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
//        _camera->TakeRot(delta,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
//        _camera->TakeRot(-delta,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
//        _camera->SetLookTarget(ayy::Vec3f(-2,0,-1));
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
//        _camera->SetLookTarget(ayy::Vec3f(-10,0,-1));
    }
    
    
    /*
    int mouseLeftBtnState,mouseRightBtnState;
    mouseLeftBtnState = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    if(mouseLeftBtnState == GLFW_PRESS)
    {
        _camera->TakeRot(0, delta,0);
    }
    
    mouseRightBtnState = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
    if(mouseRightBtnState == GLFW_PRESS)
    {
        _camera->TakeRot(0,-delta,0);
    }
    */

}
