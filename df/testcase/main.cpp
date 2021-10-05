//
//  main.cpp
//  df
//
//  Created by bytedance on 2021/9/28.
//

#include <iostream>
#include "AppDelegate.h"

int main(int argc, const char * argv[]) {
    
    AppDelegate* app = new AppDelegate();
//    app->SetDesireFPS(1);
    app->Run();
    delete app;
    return 0;
}
