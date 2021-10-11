//
//  main.cpp
//  df
//
//  Created by bytedance on 2021/9/28.
//

#include <iostream>
#include "AppDelegate.h"

#include <map>
#include <vector>
#include <functional>
#include <cstdio>

using Func = std::function<void()>;

struct Listener
{
    Func f = nullptr;
};

std::vector<Listener*> listeners;
void call2()
{
    for(auto it : listeners)
    {
        if(it->f != nullptr)
        {
            it->f();
        }
    }
}

void test2()
{
    Listener l1;
    l1.f = [](){
        printf("This is l1\n");
    };
    
    Listener l2;
    l2.f = [](){
        printf("This is l2\n");
    };
    
    listeners.push_back(&l1);
    listeners.push_back(&l2);
    
    call2();
    
    auto it = std::find(listeners.begin(),listeners.end(),&l1);
    if(it != listeners.end())
    {
        listeners.erase(it);
    }
    
    call2();
}


class Base
{
public:
    virtual ~Base() {
        printf("~Base\n");
    }
};

class C1 : public Base
{
public:
    virtual ~C1() {
        printf("~C1\n");
    }
};

int main(int argc, const char * argv[])
{
//    test2();
    
    Base* c = new C1();
    delete c;
    
    AppDelegate* app = new AppDelegate();
//    app->SetDesireFPS(1);
    app->Run();
    delete app;
    return 0;
}
