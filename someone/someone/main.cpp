//
//  main.cpp
//  someone
//
//  Created by bytedance on 2021/5/23.
//
#include "Ayy.h"
#include "ModelImporter.h"

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
#include "Lesson13.h"
#include "Lesson14.h"
#include "Lesson15.h"
#include "Lesson16.h"
#include "Lesson17.h"
#include "Lesson18.h"
#include "Lesson19.h"
#include "Lesson20.h"
#include "Lesson21.h"
#include "Crude/Crude1.h"
#include "Crude/Crude2.h"
#include "Crude/Crude3.h"
#include "Crude/Crude4.h"

const unsigned int kScreenWidth = 800;
const unsigned int kScreenHeight = 600;

int main(int argc, const char * argv[])
{
    ayy::BaseApplication app;
    
    int viewportWidth,viewportHeight;
    app.Setup();
    app.CreateWindow(kScreenWidth,kScreenHeight);
    app.GetFramebufferSize(viewportWidth,viewportHeight);
    
//    app.GetGUIDelegate()->SetFuncCallback(SceneSelectionGUI);
    
    ayy::meshv2::ModelImporter imp;
    imp.CreateModel();
    
    
    ayy::BaseScene* scene = nullptr;
//    scene = new Crude2(viewportWidth,viewportHeight);       // Demo Game
//    scene = new Crude3(viewportWidth,viewportHeight);       // Shadow map
    scene = new Crude4(viewportWidth,viewportHeight);       // Shadow map
//    scene = new Crude1(kScreenWidth,kScreenHeight);       // GPU instance
//    scene = new Lesson9(kScreenWidth,kScreenHeight);       // base light
//    scene = new Lesson21(kScreenWidth,kScreenHeight);       // text rendering
//    scene = new Lesson20(kScreenWidth,kScreenHeight);         // normal map
//    scene = new Lesson19(kScreenWidth,kScreenHeight);       // cube map
//    scene = new Lesson18(kScreenWidth,kScreenHeight);
//    scene = new Lesson17(kScreenWidth,kScreenHeight);
//    scene = new Lesson16(kScreenWidth,kScreenHeight);
//    scene = new Lesson14(kScreenWidth,kScreenHeight);
//        scene = new Lesson13(kScreenWidth,kScreenHeight);
//    scene = new Lesson8(kScreenWidth,kScreenHeight);
//    scene = new Lesson12(kScreenWidth,kScreenHeight);
//    scene = new Lesson18(kScreenWidth,kScreenHeight);
    
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
