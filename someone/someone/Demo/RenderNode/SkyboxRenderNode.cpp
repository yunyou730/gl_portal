
#include "SkyboxRenderNode.h"
#include "../Manager/ShaderManager.h"

namespace crude {

SkyboxRenderNode::SkyboxRenderNode(const SkyboxTextureParam& textureParam)
    :_textureParam(textureParam)
{
    
}

SkyboxRenderNode::~SkyboxRenderNode()
{
    CleanUp();
}

void SkyboxRenderNode::Initiate()
{
    PrepareMesh();
    _shader = BaseManager::GetInstance<ShaderManager>()->LoadProgram("res/demo/skybox.vs","res/demo/skybox.fs");
    
    _cubeTex = ayy::TextureManager::GetInstance()->CreateCubeTexture(_textureParam.rightImagePath,
                                                                       _textureParam.leftImagePath,
                                                                       _textureParam.upImagePath,
                                                                       _textureParam.bottomImagePath,
                                                                       _textureParam.backImagePath,
                                                                       _textureParam.frontImagePath);
    
    _renderState.bEnableDepthWrite = false;
}

void SkyboxRenderNode::CleanUp()
{
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
    _vao = 0;
    _vbo = 0;
    _ebo = 0;
}

void SkyboxRenderNode::OnUpdate(float deltaTime)
{
    
}

void SkyboxRenderNode::OnDraw(ayy::Camera* camera,ayy::Mat4x4f* worldMatrix)
{   
    _shader->Use();
    
    _shader->SetUniformMat4x4("u_View",(GLfloat*)camera->GetViewMatrix().data);
    _shader->SetUniformMat4x4("u_Projection",(GLfloat*)camera->GetProjMatrix().data);
    
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,(void*)0);
    
    _shader->UnUse();
}

void SkyboxRenderNode::PrepareMesh()
{
    /*
        Cube
     **/
    float vertices[] = {
        -1.0,-1.0, 1.0,
        -1.0, 1.0, 1.0,
         1.0,-1.0, 1.0,
         1.0, 1.0, 1.0,
        
        -1.0,-1.0,-1.0,
        -1.0, 1.0,-1.0,
         1.0,-1.0,-1.0,
         1.0, 1.0,-1.0,
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
    
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);
    
    // vao
    glBindVertexArray(_vao);
    {
        // vbo
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            // quad vertice data
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

            // attribute location 0,pos
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
//            // attribute location 1,uv
//            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
//            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        // ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    }
    
    glBindVertexArray(0);
    
}


}


