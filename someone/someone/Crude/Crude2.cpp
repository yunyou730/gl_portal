#include "Crude2.h"
#include <sstream>

#include "../Demo/FreeCamera.h"
#include "../Demo/Wall.h"
#include "../Demo/Ground.h"


#include "../Demo/ecs/Util.h"

#include "../Demo/ecs/World.h"
#include "../Demo/ecs/BaseEntity.h"

#include "../Demo/ecs/BaseComponent.h"
#include "../Demo/ecs/RenderComponent.h"
#include "../Demo/ecs/TransformComponent.h"
#include "../Demo/ecs/CameraComponent.h"
#include "../Demo/ecs/KeyboardInputComponent.h"

#include "../Demo/ecs/RenderSystem.h"
#include "../Demo/ecs/InputSystem.h"

#include "../Demo/ecs/MapSingleton.h"

Crude2::Crude2(int viewportWidth,int viewportHeight)
    :ayy::BaseScene(viewportWidth,viewportHeight)
{
    
}

Crude2::~Crude2()
{
    
}

void Crude2::Prepare()
{
    // ECS world
    _world = new crude::World();
    _world->RegisterRenderSystem<crude::RenderSystem>();
    _world->RegisterInputSystem<crude::InputSystem>();
    
    InitMap();
    auto camera = InitMainCamera();
    InitGround(camera);
    
    
    // wall
    crude::BaseEntity* wallEntity = _world->CreateEntity();
    auto render = dynamic_cast<crude::RenderComponent*>(wallEntity->AddComp(crude::ECompType::Render));
    render->SetWatchCamera(camera);
    auto transform = dynamic_cast<crude::TransformComponent*>(wallEntity->AddComp(crude::ECompType::Transform));
    
    auto _wall = new crude::Wall();
    _wall->Initiate();
    render->SetRenderNode(_wall);
    transform->SetPos(ayy::Vec3f(0,0,0));
}

void Crude2::InitMap()
{
    crude::MapSingleton* map = _world->RegisterSingleton<crude::ESingleton::Map, crude::MapSingleton>();
    map->InitDefaultValue();
}

ayy::Camera* Crude2::InitMainCamera()
{
    auto camera = new crude::FreeCamera(GetViewportWidth(),GetViewportHeight());
    camera->SetPos(ayy::Vec3f(0,1,1));
    camera->SetLookDir(ayy::Vec3f(0,0,0) - ayy::Vec3f(0,1,1));
    
    crude::BaseEntity* cameraEntity = _world->CreateEntity();
    crude::CameraComponent* cameraComp = dynamic_cast<crude::CameraComponent*>(cameraEntity->AddComp(crude::ECompType::Camera));
    cameraEntity->AddComp(crude::ECompType::KeyboardInput);
    
    cameraComp->SetCamera(camera);
    
    return camera;
}

void Crude2::InitGround(ayy::Camera* camera)
{
    // ground entity
    crude::BaseEntity* groundEntity = _world->CreateEntity();
    auto render = dynamic_cast<crude::RenderComponent*>(groundEntity->AddComp(crude::ECompType::Render));
    auto transform = dynamic_cast<crude::TransformComponent*>(groundEntity->AddComp(crude::ECompType::Transform));
    
    auto _ground = new crude::Ground();
    _ground->Initiate();
    render->SetRenderNode(_ground);
    render->SetWatchCamera(camera);
    transform->SetPos(ayy::Vec3f(0,0,0));
    
    auto map = _world->GetSingleton<crude::MapSingleton>(crude::ESingleton::Map);
    float unitSize = crude::Util::GetUnitSize();
    transform->SetScale(ayy::Vec3f(unitSize * map->GetCols(),unitSize,unitSize * map->GetRows()));
}

void Crude2::Cleanup()
{
    AYY_SAFE_DEL(_world);
}

void Crude2::OnUpdate()
{
    _world->OnUpdate(GetDeltaTime());
}

void Crude2::OnRender()
{
    _world->OnRender();
}

void Crude2::HandleKeyboardInput(GLFWwindow* window)
{
    _world->OnKeyboardInput(window,GetDeltaTime());
}
