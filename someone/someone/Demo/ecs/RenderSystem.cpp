#include "RenderSystem.h"
#include "BaseEntity.h"
#include "World.h"
#include "../RenderNode.h"
#include "RenderComponent.h"

namespace crude {

RenderSystem::RenderSystem(World* world)
    :BaseSystem(world)
{
    
}

void RenderSystem::Init()
{
    
}

void RenderSystem::Update(float deltaTime)
{
    
}

void RenderSystem::OnRender()
{
    std::vector<BaseEntity*> entities = GetWorld()->QueryEntities({ECompType::Render,ECompType::Transform});
    for(auto it : entities)
    {
        RenderComponent* renderComp = dynamic_cast<RenderComponent*>(it->GetComp(ECompType::Render));
        RenderNode* node = renderComp->_renderNode;
        node->OnDraw(renderComp->_watchCamera);
    }
}

void RenderSystem::Cleanup()
{
    
}

}
