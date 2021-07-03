#include "LessonBase.h"

LessonBase::LessonBase(int viewportWidth,int viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
{
    
}

void LessonBase::OnUpdate()
{
    
}

void LessonBase::HandleKeyboardInput(GLFWwindow* window)
{
    
}

void LessonBase::OnViewportSizeChanged(int width,int height)
{
    _viewportWidth = width;
    _viewportHeight = height;
}
