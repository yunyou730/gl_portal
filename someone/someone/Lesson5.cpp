#include "Lesson5.h"
#include "../ayy/headers/Shader.h"
#include "../ayy/headers/Util.h"
#include "stb_image.h"

const int kIndiceCount = 6;

Lesson5::~Lesson5()
{
    
}

void Lesson5::Prepare()
{
    _shader = ayy::Util::CreateShaderWithFile("res/color_texture.vs", "res/color_texture.fs");
    PrepareMesh(_vao,_vbo,_ebo);
    PrepareTexture(_tID);
}

void Lesson5::Cleanup()
{
    delete _shader;
    glDeleteVertexArrays(1,&_vao);
    glDeleteBuffers(1,&_vbo);
    glDeleteBuffers(1,&_ebo);
}

void Lesson5::OnUpdate()
{
    _shader->Use();
    
    // @miao @todo
    // using texture
    glActiveTexture(0);
    glUniform1i(glGetUniformLocation(_shader->program,"myTex"),0);
    
    
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES,kIndiceCount,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Lesson5::PrepareMesh(GLuint& VAO,GLuint& VBO,GLuint& EBO)
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

void Lesson5::PrepareTexture(GLuint& tid)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load("res/container.jpg", &width, &height, &nrChannels, 0);
    printf("%d,%d,%d\n",width,height,nrChannels);

    GLuint textureID;
    glGenTextures(1,&textureID);
    
    /*
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);    // 有这句才能显示出来，没有不行 !

    stbi_image_free(data);
}
