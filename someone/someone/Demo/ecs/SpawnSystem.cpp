#include "SpawnSystem.h"
#include "BaseEntity.h"
#include "World.h"
#include "SpawnSingleton.h"

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "KeyboardInputComponent.h"

#include "../FreeCamera.h"
#include "../RenderNode/Wall.h"
#include "../RenderNode/Ground.h"
#include "../RenderNode/BlockRender.h"

#include "Util.h"

namespace crude {

SpawnSystem::SpawnSystem(World* world)
    :BaseSystem(world)
{
    
}

void SpawnSystem::Init()
{
    _spawn = _world->GetSingleton<crude::SpawnSingleton>(ESingleton::ST_Spawn);
}

void SpawnSystem::OnUpdate(float deltaTime)
{
    for(auto it :_spawn->_toSpawn)
    {
        DoSpawn(&it);
    }
    _spawn->ClearData();
}

void SpawnSystem::OnRender()
{
    
}

void SpawnSystem::Cleanup()
{
    
}

void SpawnSystem::DoSpawn(SpawnParam* param)
{
    switch(param->actorType)
    {
        case crude::EActorType::AT_Block:
        {
            crude::BaseEntity* entity = _world->CreateEntity();
            auto render = entity->AddComponent<crude::RenderComponent>(crude::ECompType::Render);
            
            auto transform =  entity->AddComponent<crude::TransformComponent>(crude::ECompType::Transform);
            
            auto block = new crude::BlockRender();
            block->Initiate();
            render->SetRenderNode(block);
            transform->SetPos(Util::GetPosAtTile(param->atRow, param->atCol));
            
            float unitSize = Util::GetUnitSize();
            transform->SetScale(ayy::Vec3f(unitSize,unitSize,unitSize));
        }
        break;
            
        default:
            break;
    }
    
}

}
