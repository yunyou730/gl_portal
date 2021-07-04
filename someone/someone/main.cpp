//
//  main.cpp
//  someone
//
//  Created by bytedance on 2021/5/23.
//

#include "BaseApplication.h"

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
#include "Lesson11.h"
#include "Lesson12.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void test()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("ssss", aiProcess_Triangulate | aiProcess_FlipUVs);
    printf("fds\n");
}

int main(int argc, const char * argv[])
{
    test();
    
    ayy::BaseApplication app;
    
    app.Setup();
    app.CreateWindow();
    
    Lesson12 lesson(SCR_WIDTH,SCR_HEIGHT);
//    Lesson11 lesson(SCR_WIDTH,SCR_HEIGHT);
//    Lesson8 lesson;
    lesson.Prepare();
    
    app.SetScene(&lesson);
    app.MainLoop();
    
    lesson.Cleanup();
    
    app.Cleanup();
    return 0;
}
