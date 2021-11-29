#include "InputSystem.h"
#include "BaseEntity.h"
#include "World.h"
#include "CameraComponent.h"
#include "KeyboardInputComponent.h"

#include "Ayy.h"
#include "FreeCamera.h"

namespace crude {

InputSystem::InputSystem(World* world)
    :BaseSystem(world)
{
    
}

void InputSystem::OnKeyboardInput(GLFWwindow* window,float deltaTime)
{
    auto entities = GetWorld()->QueryEntities({ECompType::Camera,ECompType::KeyboardInput});
    for(auto it : entities)
    {
        auto cameraComp = dynamic_cast<crude::CameraComponent*>(it->GetComp(ECompType::Camera));
        ayy::Camera* cam = cameraComp->_camera;
        dynamic_cast<crude::FreeCamera*>(cam)->HandleKeyboardInput(window,deltaTime);
    }
}

}
