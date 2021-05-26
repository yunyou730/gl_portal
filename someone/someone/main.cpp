//
//  main.cpp
//  someone
//
//  Created by bytedance on 2021/5/23.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ayy/headers/Shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow *window);


const char* vsSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(vec3(aPos), 1.0);
}
)";

const char* fsSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0,0.5,0.2,1.0);
}
)";

void prepareMesh(GLuint& VAO,GLuint& VBO);

int main(int argc, const char * argv[]) {
    
    // init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // create window with glfw
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // enable glad
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    
    // draw prepare
    auto shader = ayy::ShaderProgram::CreateShaderProgram(vsSource, fsSource);
    
    GLuint VAO,VBO;
    prepareMesh(VAO,VBO);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // Render code here
        glClear(GL_COLOR_BUFFER_BIT);   // render begin
        
        // Do Render
        glUseProgram(shader->program);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES,0,3);
        
        
        // render end
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    delete shader;
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
//    glViewport(0,0,width,height);
//    printf("%d,%d\n",width,height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// set up vertex data (and buffer(s)) and configure vertex attributes
void prepareMesh(GLuint& VAO,GLuint& VBO)
{
    // NDC xyz [-1,1]
    float vertices[] = {
        -0.5f,-0.5f,0.0f,       // left
         0.5f,-0.5f,0.0f,       // right
         0.0f, 0.5f,0.0f,       // top
    };
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    
    size_t s = sizeof(vertices);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
        }
        // unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    // unbind VAO
    glBindVertexArray(0);
    
}
