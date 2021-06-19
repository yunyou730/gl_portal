#include "Lesson8.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "../ayy/headers/Camera.h"
#include "TextureManager.h"

const int kIndiceCount = 18;

Lesson8::Lesson8(int viewportWidth,int viewportHeight)
    :LessonBase(viewportWidth,viewportHeight)
{
    
}

Lesson8::~Lesson8()
{
    
}

void Lesson8::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/mvp_test_2.vs","res/mvp_test_2.fs");
    PrepareMesh(_vao,_vbo,_ebo);
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
    
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
    
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
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,kIndiceCount,GL_UNSIGNED_INT,(void*)0);
    
    glBindVertexArray(0);
    _shader->UnUse();
}

void Lesson8::PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO)
{
    // rectangle
    float vertices[] = {
        // front
        -0.5f,-0.5f,0.0f,       // left bottom pos
         0.0f, 0.0f,            // uv
        
        -0.5f, 0.5f,0.0f,       // left top
         0.0f, 1.0f,            // uv
        
         0.5f,-0.5f,0.0f,       // right bottom
         1.0f, 0.0f,            // uv
        
         0.5f, 0.5f,0.0f,       // right top
         1.0f, 1.0f,            // uv
        
        
        // back
        -0.5f,-0.5f,1.0f,       // left bottom pos
         0.0f, 0.0f,            // uv
        
        -0.5f, 0.5f,1.0f,       // left top
         0.0f, 1.0f,            // uv
        
         0.5f,-0.5f,1.0f,       // right bottom
         1.0f, 0.0f,            // uv
        
         0.5f, 0.5f,1.0f,       // right top
         1.0f, 1.0f,            // uv
    };
    
    
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
        1,3,2,
        
        4,5,6,
        5,7,6,
        
        4,5,0,
        5,1,0,
    };
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            
            // attribute location 0,pos data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,uv data
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        
        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
    glBindVertexArray(0);
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
    
//    _shader->SetUniformMat4x4("uScale",(GLfloat*)matScale.data);
//    _shader->SetUniformMat4x4("uRotateZ",(GLfloat*)matRotateByZ.data);
//    _shader->SetUniformMat4x4("uTranslate",(GLfloat*)matTranslate.data);
//    _shader->SetUniformMat4x4("uView", (GLfloat*)_camera->GetViewMatrix().data);
//    _shader->SetUniformMat4x4("uProject",(GLfloat*)_camera->GetProjMatrix().data);
    
//     mvp
    ayy::Mat4x4f matModel = matScale * matRot * matTranslate;
    ayy::Mat4x4f matMVP = matModel * _camera->GetViewMatrix() * _camera->GetProjMatrix();
    _shader->SetUniformMat4x4("uMVP",(GLfloat*)matMVP.data);
    
    
    matModel.Dump();
    _camera->GetViewMatrix().Dump();
    _camera->GetProjMatrix().Dump();
    matMVP.Dump();
    
    
    ayy::Vec4f test;
    test.SetX(-0.5f);
    test.SetY(-0.5f);
    test.SetZ( 0.0f);
    test.SetW( 1.0f);
    
    test.Dump();
    matMVP.Dump();
    
    ayy::Vec4f t2 = test * matMVP;
    
    t2.Dump();
}

void Lesson8::HandleKeyboardInput(GLFWwindow* window)
{
    // handle camera move
    float delta = GetDeltaTime() * _camMoveSpeed;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        _camera->TakeMove(0.0f, delta, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        _camera->TakeMove(0.0f, -delta, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        _camera->TakeMove(-delta, 0.0f, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera->TakeMove(delta, 0.0f, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        _camera->TakeMove(0.0f, 0.0f, delta);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        _camera->TakeMove(0.0f, 0.0f, -delta);
    }
    
    // handle camera rot
    delta = GetDeltaTime() * _camRotSpeed;
    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        _camera->TakeRot(0,0,-delta);
    }
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        _camera->TakeRot(0,0,delta);
    }
    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        _camera->TakeRot(delta,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        _camera->TakeRot(-delta,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        _camera->TakeRot(0.0f,delta, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        _camera->TakeRot(0.0f,-delta,0.0f);
    }
    
    // handle box rot
    delta = _rotSpeed * GetDeltaTime();
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        _rot.SetX(_rot.x() + delta);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        _rot.SetX(_rot.x() - delta);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        _rot.SetZ(_rot.z() - delta);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        _rot.SetZ(_rot.z() + delta);
    }
}
