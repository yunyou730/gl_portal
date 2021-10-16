#include "RenderSystem.h"
#include "BaseEntity.h"
#include "World.h"
#include "../RenderNode/RenderNode.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CameraSingleton.h"

namespace crude {

RenderSystem::RenderSystem(World* world)
    :BaseSystem(world)
{
    
}

void RenderSystem::Init()
{
    _camera = _world->GetSingleton<CameraSingleton>(ESingleton::ST_Camera);
}

void RenderSystem::OnUpdate(float deltaTime)
{
    
}

void RenderSystem::OnRender()
{
    std::vector<BaseEntity*> entities = GetWorld()->QueryEntities({ECompType::Render,ECompType::Transform});
    for(auto it : entities)
    {
        RenderComponent* renderComp = dynamic_cast<RenderComponent*>(it->GetComp(ECompType::Render));
        RenderNode* node = renderComp->_renderNode;
        
        auto transformComp = dynamic_cast<TransformComponent*>(it->GetComp(ECompType::Transform));
        node->OnDraw(_camera->GetMainCamera(),transformComp->GetWorldMatrix());
    }
}

void RenderSystem::Cleanup()
{
    
}

}
