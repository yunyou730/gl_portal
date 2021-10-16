#include "Crude2.h"
#include <sstream>

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
#include "../Demo/ecs/SpawnSystem.h"

#include "../Demo/ecs/MapSingleton.h"
#include "../Demo/ecs/SpawnSingleton.h"
#include "../Demo/ecs/CameraSingleton.h"

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
    auto spawn = _world->RegisterSingleton<crude::ESingleton::ST_Spawn, crude::SpawnSingleton>();
    auto cameraSingle = _world->RegisterSingleton<crude::ESingleton::ST_Camera, crude::CameraSingleton>();
    
    _world->RegisterRenderSystem<crude::RenderSystem>();
    _world->RegisterInputSystem<crude::InputSystem>();
    _world->RegisterUpdateSystem<crude::SpawnSystem>();
    
    
    map->InitDefaultValue();

    auto camera = InitMainCamera();
    cameraSingle->RegisterCamera(camera);
    
    spawn->AddSpawnData(crude::SpawnParam(crude::EActorType::AT_Block,3,2));
    spawn->AddSpawnData(crude::SpawnParam(crude::EActorType::AT_Block,3,3));
    spawn->AddSpawnData(crude::SpawnParam(crude::EActorType::AT_Block,5,2));
    

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
    
    // Block test
    {
        crude::BaseEntity* entity = _world->CreateEntity();
        auto render = entity->AddComponent<crude::RenderComponent>(crude::ECompType::Render);
        auto transform =  entity->AddComponent<crude::TransformComponent>(crude::ECompType::Transform);
        
        auto block = new crude::BlockRender();
        block->Initiate();
        render->SetRenderNode(block);
        transform->SetPos(ayy::Vec3f(2,3,5));
        transform->SetScale(ayy::Vec3f(1,1,1));
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
