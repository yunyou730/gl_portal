#include "Crude2.h"
#include <sstream>

#include "../Demo/ecs/Util.h"

#include "../Demo/ecs/World.h"
#include "../Demo/ecs/BaseEntity.h"

#include "../Demo/ecs/Component/BaseComponent.h"
#include "../Demo/ecs/Component/RenderComponent.h"
#include "../Demo/ecs/Component/TransformComponent.h"
#include "../Demo/ecs/Component/CameraComponent.h"
#include "../Demo/ecs/Component/KeyboardInputComponent.h"

#include "../Demo/ecs/System/RenderSystem.h"
#include "../Demo/ecs/System/InputSystem.h"
#include "../Demo/ecs/System/SpawnSystem.h"
#include "../Demo/ecs/System/InitializeSystem.h"
#include "../Demo/ecs/System/PerformanceSystem.h"

#include "../Demo/ecs/Singleton/MapSingleton.h"
#include "../Demo/ecs/Singleton/SpawnSingleton.h"
#include "../Demo/ecs/Singleton/CameraSingleton.h"
#include "../Demo/ecs/Singleton/PerformanceSingleton.h"

#include "../Demo/FreeCamera.h"
#include "../Demo/RenderNode/Wall.h"
#include "../Demo/RenderNode/Ground.h"
#include "../Demo/RenderNode/BlockRender.h"

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
    
    auto map = _world->RegisterSingleton<crude::ESingleton::ST_Map, crude::MapSingleton>();
    auto cameraSingle = _world->RegisterSingleton<crude::ESingleton::ST_Camera, crude::CameraSingleton>();
    _world->RegisterSingleton<crude::ESingleton::ST_Spawn, crude::SpawnSingleton>();
    _world->RegisterSingleton<crude::ESingleton::ST_Performance,crude::PerformanceSingleton>();
    
    map->InitDefaultValue();

    auto camera = InitMainCamera();
    cameraSingle->RegisterCamera(camera);
    
    _world->RegisterUpdateSystem<crude::InitializeSystem>();
    _world->RegisterRenderSystem<crude::RenderSystem>();
    _world->RegisterInputSystem<crude::InputSystem>();
    _world->RegisterUpdateSystem<crude::SpawnSystem>();
    _world->RegisterUpdateSystem<crude::PerformanceSystem>();
    
    InitGround();
    
    // wall
    {
        crude::BaseEntity* wallEntity = _world->CreateEntity();
        auto render = wallEntity->AddComponent<crude::RenderComponent>(crude::ECompType::Render);
        auto transform = wallEntity->AddComponent<crude::TransformComponent>(crude::ECompType::Transform);
        
        auto wall = new crude::Wall();
        wall->Initiate();
        render->SetRenderNode(wall);
        transform->SetPos(ayy::Vec3f(0,0,0));
    }
}

void Crude2::InitMap()
{

}

ayy::Camera* Crude2::InitMainCamera()
{
    auto camera = new crude::FreeCamera(GetViewportWidth(),GetViewportHeight());
    
    ayy::Vec3f defaultPos = ayy::Vec3f(0,2,3);
    camera->SetPos(defaultPos);
    camera->SetLookDir(ayy::Vec3f(0,0,0) - defaultPos);
    
    crude::BaseEntity* cameraEntity = _world->CreateEntity();
    auto cameraComp = cameraEntity->AddComponent<crude::CameraComponent>(crude::ECompType::Camera);
    cameraEntity->AddComponent<crude::KeyboardInputComponent>(crude::ECompType::KeyboardInput);
    
    cameraComp->SetCamera(camera);
    
    return camera;
}

void Crude2::InitGround()
{
    // ground entity
    crude::BaseEntity* groundEntity = _world->CreateEntity();
    auto render = groundEntity->AddComponent<crude::RenderComponent>(crude::ECompType::Render);
    auto transform = groundEntity->AddComponent<crude::TransformComponent>(crude::ECompType::Transform);
    
    auto _ground = new crude::Ground();
    _ground->Initiate();
    render->SetRenderNode(_ground);
    transform->SetPos(ayy::Vec3f(0,0,0));
    
    // ground size
    auto map = _world->GetSingleton<crude::MapSingleton>(crude::ESingleton::ST_Map);
    float unitSize = crude::Util::GetUnitSize();
    transform->SetScale(ayy::Vec3f(unitSize * map->GetCols(),unitSize,unitSize * map->GetRows()));
    
    // ground render param
    _ground->GetRenderParam()->cols = map->GetCols();
    _ground->GetRenderParam()->rows = map->GetRows();
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
