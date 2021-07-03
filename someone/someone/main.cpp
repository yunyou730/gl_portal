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

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

ayy::BaseScene* lesson = nullptr;


int main(int argc, const char * argv[])
{
    
    ayy::BaseApplication app;
    
    app.Setup();
    app.CreateWindow();
    

    lesson = new Lesson10(SCR_WIDTH,SCR_HEIGHT);
//    lesson = new Lesson3();
    lesson->Prepare();
    
    app.SetScene(lesson);
    
    app.MainLoop();
    
    lesson->Cleanup();
    delete lesson;
    lesson = nullptr;
    
    app.Cleanup();
    return 0;
}
