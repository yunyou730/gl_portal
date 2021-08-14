//
//  main.cpp
//  someone
//
//  Created by bytedance on 2021/5/23.
//
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
#include "Lesson13.h"
#include "Lesson14.h"
#include "Lesson15.h"
#include "Lesson16.h"
#include "Lesson17.h"
#include "Lesson18.h"
#include "Lesson19.h"
#include "Lesson20.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static ayy::BaseApplication app;
static ayy::BaseScene* scene = nullptr;

void ChooseSceneGUI()
{
    static int item_current = 0;
    static const char* items[] = { "lesson13", "lesson12", "lesson11","lesson10","lesson9","lesson8","lesson7","lesson6","lesson5","lesson4","lesson3","lesson2","lesson1"};
    
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
                scene = new Lesson13(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 1:
                scene = new Lesson12(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 2:
                scene = new Lesson11(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 3:
                scene = new Lesson10(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 4:
                scene = new Lesson9(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 5:
                scene = new Lesson8(SCR_WIDTH,SCR_HEIGHT);
                break;
            case 6:
                scene = new Lesson7();
                break;
            case 7:
                scene = new Lesson6();
                break;
            case 8:
                scene = new Lesson5();
                break;
            case 9:
                scene = new Lesson4();
                break;
            case 10:
                scene = new Lesson3();
                break;
            case 11:
                scene = new Lesson2();
                break;
            case 12:
                scene = new Lesson1();
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
    app.Setup();
    app.CreateWindow();
    
    app.GetGUIDelegate()->SetFuncCallback(ChooseSceneGUI);

    scene = new Lesson20(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson19(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson18(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson17(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson16(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson14(SCR_WIDTH,SCR_HEIGHT);
//        scene = new Lesson13(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson8(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson12(SCR_WIDTH,SCR_HEIGHT);
//    scene = new Lesson18(SCR_WIDTH,SCR_HEIGHT);
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
