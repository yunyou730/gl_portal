#include "AYYBaseScene.h"

namespace ayy {

BaseScene::BaseScene(int viewportWidth,int viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
{
    
}

void BaseScene::OnUpdate()
{
    
}

void BaseScene::OnGUI()
{
    
}

void BaseScene::HandleKeyboardInput(GLFWwindow* window)
{
    
}

void BaseScene::OnViewportSizeChanged(int width,int height)
{
    _viewportWidth = width;
    _viewportHeight = height;
}

}
