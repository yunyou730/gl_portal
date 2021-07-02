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
#include "Lesson5.h"
#include "Lesson6.h"
#include "Lesson7.h"
#include "Lesson8.h"
#include "Lesson9.h"
#include "Lesson10.h"

#include "Math.h"
#include "IO.h"
#include "stb_image.h"
#include "Texture.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

LessonBase* lesson = nullptr;

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow *window);

void test()
{
    ayy::Vec3f v2(1,-2,5);
    printf("len %f\n",v2.Length());
    
    v2.Normalize();
    printf("len %f\n",v2.Length());
    
    v2 = v2 * 100;
    v2.Dump();
    printf("len %f\n",v2.Length());

    
    v2 = 10.f * v2;
    v2.Dump();
    printf("len %f\n",v2.Length());
    
    ayy::Vec3f v3;
    printf("len %f\n",v3.Length());
    v3.Dump();
    
    v3 = v3 + ayy::Vec3f(1,-1,3);
    v3.Dump();
    
    printf("\ndot %f\n",v3.Dot(v2));
    
    v3 = v3 * 3;
    v3.Dump();
    
    ayy::Vec4f v4(1,2,3,1);
    
    ayy::Mat4x4f mat;
//    mat.Identify();
    int idx = 0;
    for(int r = 0;r < 4;r++)
    {
        for(int c = 0;c < 4;c++)
        {
            mat.Set(r,c,idx);
            idx++;
        }
    }
    mat.Dump();
    
    ayy::Mat4x4f mat2;
    mat2.Identify();
    mat2.Set(0,0,2);
    mat2.Set(3,2,5);
    mat2.Dump();
    
    (mat * mat2).Dump();
    
    ayy::Vec4f pos(1,1,1,1);
    pos = pos * mat2;
    pos.Dump();
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
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);
    
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
    
    
    lesson = new Lesson10(SCR_WIDTH,SCR_HEIGHT);
//    lesson = new Lesson3();
    lesson->Prepare();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    static double lastFrameTime = glfwGetTime();
    
    while(!glfwWindowShouldClose(window))
    {
        // Render code here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // render begin
        
        double curTime = glfwGetTime();
        float deltaTime = curTime - lastFrameTime;
        lesson->SetDeltaTime(deltaTime);
        lastFrameTime = curTime;
        
        lesson->OnUpdate();
        lesson->OnRender(deltaTime);

        // render end
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // frame logic
        processInput(window);
    }
    
    lesson->Cleanup();
    delete lesson;
    lesson = nullptr;
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
//    glViewport(0,0,width,height);
//    printf("%d,%d\n",width,height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    
    if(lesson != nullptr)
    {
        lesson->HandleKeyboardInput(window);
    }
}

