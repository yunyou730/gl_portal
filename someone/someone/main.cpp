//
//  main.cpp
//  someone
//
//  Created by bytedance on 2021/5/23.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Lesson1.h"
#include "Lesson2.h"
#include "Lesson3.h"
#include "Lesson4.h"

#include "Math.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow *window);


void test()
{
    ayy::Vec4<float> v;
    printf("%.3f",v[0]);
    v.x = 3.0f;
    printf("%.3f",v[0]);
    
    ayy::Vec4<int> v2(1,2,3,4);
    printf("%d,%d,%d,%d",v2.x,v2.y,v2.z,v2.w);
}


int main(int argc, const char * argv[])
{
    
    test();
    
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
    
    
    Lesson4 lesson;
    lesson.Prepare();
    
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // Render code here
        glClear(GL_COLOR_BUFFER_BIT);   // render begin
        

        
        lesson.OnUpdate();
        
        
        // render end
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    lesson.Cleanup();
    
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

