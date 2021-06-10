//
//  Mesh.h
//  opengl_window
//
//  Created by Tina Green on 2019/10/23.
//  Copyright © 2019 Tina Green. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h
#include<glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"shader.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<cstddef>
//using namespace std;
struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 Texcoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};
struct Texture{
    unsigned int IDNum;
    std::string path;
    std::string type;
};
class Mesh
{
    public:
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;
    unsigned int VAO_ofthismesh;
    
    Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices)
    {
        this->vertices=vertices;
        this->textures=textures;
        this->indices=indices;
        setupMesh();
    }
    
    void Draw(Shader shader_model ,bool outline,bool reflect)
    {//让uniform与textureID取得联系
        if(outline==true){
            //glEnable(GL_STENCIL_TEST);
            //glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
            //glClear(GL_STENCIL_BUFFER_BIT);
            glStencilFunc(GL_ALWAYS,1,0xFF);
            glStencilMask(0xFF);
        }
        if(!reflect)//if reflect, bind model diffuse texture
        {
        unsigned int diffuseNr=1;
        unsigned int specularNr=1;
        unsigned int normalNr=1;
        unsigned int heightNr=1;
        unsigned int ambientNr=1;
        for(int i=0;i<textures.size();i++)
            {
                std::string name=textures[i].type;
                std::string number;
                if(name=="texture_diffuse")
                    number=std::to_string(diffuseNr++);//to_string是int转为string用的函数
                else if(name=="texture_specular")
                    number=std::to_string(specularNr++);
                else if(name=="texture_normal")
                    number=std::to_string(normalNr++);
                else if(name=="texture_height")
                    number=std::to_string(heightNr++);
                else if(name=="texture_ambient")
                    number==std::to_string(ambientNr++);
                glActiveTexture(GL_TEXTURE0+i);
                glBindTexture(GL_TEXTURE_2D,textures[i].IDNum);
                std::string uniformname="material."+name+number;
                glUniform1i(glad_glGetUniformLocation(shader_model.id,uniformname.c_str()),i);
                glUniform1f(glad_glGetUniformLocation(shader_model.id,"material.shininess"),32);
            }
        }
        glBindVertexArray(VAO_ofthismesh);
        glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);//draw model
        //draw outline
        if(outline==true)
        {
            //glStencilFunc(GL_NOTEQUAL,1,0XFF);
            glStencilMask(0x00);
            glStencilFunc(GL_NOTEQUAL,1,0XFF);
            //glDisable(GL_DEPTH_TEST);//z=0.99f
            shader_model.setbool("outline_vert",true);
            shader_model.setbool("outline_frag", true);
            glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
            glStencilMask(0xFF);
            //glEnable(GL_DEPTH_TEST);
            shader_model.setbool("outline_vert",false);
            shader_model.setbool("outline_frag",false);
            //glStencilMask(0x00);
        }
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
    private:
    unsigned int VBO,EBO;
    void setupMesh()
    {//设置该mesh的vao，设置vao属性等
        glGenVertexArrays(1,&VAO_ofthismesh);
        glGenBuffers(1,&VBO);
        glGenBuffers(1,&EBO);
        
        glBindVertexArray(VAO_ofthismesh);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
        
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Texcoords));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Tangent));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Bitangent));
        glEnableVertexAttribArray(4);
        
        glBindVertexArray(0);
    }
    
};




#endif /* Mesh_h */
