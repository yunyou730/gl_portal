#include "Lesson7.h"

const int kIndiceCount = 6;

Lesson7::~Lesson7()
{
    
}

void Lesson7::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/mvp_test.vs","res/mvp_test.fs");
    PrepareMesh(_vao,_vbo,_ebo);
    PrepareTexture();
}

void Lesson7::Cleanup()
{
    delete _shader;
    _shader = nullptr;
    
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
}

void Lesson7::OnRender()
{
    // using shader
    _shader->Use();
    
    // using texture
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture1,0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texture2,1);
    _shader->SetUniform("texture1",0);      // texture1 使用 GL_TEXTURE0 slot
    _shader->SetUniform("texture2",1);      // texture2 使用 GL_TEXTURE1 slot
    
    UpdateTransform(GetDeltaTime());
    
    // draw with VAO
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,kIndiceCount,GL_UNSIGNED_INT,(void*)0);
    
    glBindVertexArray(0);
    _shader->UnUse();
}

void Lesson7::PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO)
{
    // rectangle
    float vertices[] = {
        -0.5f,-0.5f,0.0f,       // left bottom pos
         1.0f, 0.0f,0.0f,       // red
         0.0f, 0.0f,            // uv
        
        -0.5f, 0.5f,0.0f,       // left top
         0.0f, 1.0f,0.0f,       // green
         0.0f, 1.0f,            // uv
        
         0.5f,-0.5f,0.0f,       // right bottom
         0.0f, 0.0f,1.0f,       // blue
         1.0f, 0.0f,            // uv
        
         0.5f, 0.5f,0.0f,       // right top
         1.0f, 1.0f,0.0f,       // yellow
         1.0f, 1.0f,            // uv
    };
    // rectangle indice
    unsigned int indices[] = {
        0,1,2,
        1,3,2,
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
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // attribute location 1,color data
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);
            
            // attribute location 2,uv data
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
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

void Lesson7::PrepareTexture()
{
    _texture1 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/container.jpg");
    _texture2 = ayy::TextureManager::GetInstance()->CreateTextureWithFilePath("res/awesomeface.png");
}

void Lesson7::UpdateTransform(float deltaTime)
{
    ayy::Mat4x4f matScale;
    ayy::Mat4x4f matTranslate;
    ayy::Mat4x4f matRotateByZ;
    
    ayy::MakeTranslateMatrix(matTranslate,0.5f,0,0);
    ayy::MakeScaleMatrix(matScale,0.7f);
    ayy::MakeRotateByZMatrix(matRotateByZ,ayy::DegToRad(_rotZ));
    
    _shader->SetUniformMat4x4("uScale",(GLfloat*)matScale.data);
    _shader->SetUniformMat4x4("uRotateZ",(GLfloat*)matRotateByZ.data);
    _shader->SetUniformMat4x4("uTranslate",(GLfloat*)matTranslate.data);
    
    
    _rotZ += deltaTime * _rotZSpeed;
}
