#include "AppDelegate.h"

#include "DFEvent.h"
#include "../engine/ecs/DFWorld.h"

AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
    
}

void AppDelegate::DidFinishLaunching()
{
    Application::DidFinishLaunching();
    
    GetWorld()->RegisterEvent(df::EEventType::EKeyPress,[](df::EventBase* evt)->void{
        printf("fdsfds\n");
    });
}

void AppDelegate::DidEnterBackground()
{
    Application::DidEnterBackground();
}

void AppDelegate::DidEnterForeground()
{
    Application::DidEnterForeground();
}

void AppDelegate::CleanUp()
{
    Application::CleanUp();
}
