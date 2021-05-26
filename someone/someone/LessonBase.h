#pragma once

class LessonBase
{
public:
    virtual ~LessonBase() {}
    
    virtual void Prepare() = 0;
    virtual void Cleanup() = 0;
    virtual void OnUpdate() = 0;    
};
