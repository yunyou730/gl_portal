//
//  main.cpp
//  someone
//
//  Created by bytedance on 2021/5/23.
//

#include "BaseApplication.h"
#include "Ayy.h"

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
//    Assimp::Importer importer;
//    const aiScene *scene = importer.ReadFile("res/nanosuit/nanosuit.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
//    printf("fds\n");
}

static ayy::BaseApplication app;
static ayy::BaseScene* scene = nullptr;

void ChooseSceneGUI()
{
    static int item_current = 0;
    static const char* items[] = { "lesson12", "lesson11", "lesson10"};
    
    int prevItem = item_current;
    ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));
    if(item_current != prevItem)
    {
        if(scene != nullptr)
        {
            scene->Cleanup();
            AYY_SAFE_DEL(scene);
        }
        switch(item_current)
        {
            case 0:
                scene = new Lesson12(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 1:
                scene = new Lesson11(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 2:
                scene = new Lesson10(SCR_WIDTH,SCR_HEIGHT);
                break;
            default:
                break;
        }
        scene->Prepare();
        app.SetScene(scene);
    }
}

int main(int argc, const char * argv[])
{
    test();
    
    app.Setup();
    app.CreateWindow();
    
    app.GetGUIDelegate()->SetFuncCallback(ChooseSceneGUI);
    
    scene = new Lesson12(SCR_WIDTH,SCR_HEIGHT);
    scene->Prepare();
    app.SetScene(scene);
    
    app.MainLoop();
    
    if(scene != nullptr)
    {
        scene->Cleanup();
        AYY_SAFE_DEL(scene);
    }
    
    app.Cleanup();
    return 0;
}
