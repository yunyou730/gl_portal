#pragma once

#include "../engine/core/DFApplication.h"


class AppDelegate : public df::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    
protected:
    virtual void DidFinishLaunching() override;
    virtual void DidEnterBackground() override;
    virtual void DidEnterForeground() override;
    virtual void CleanUp() override;
};
