#include "RenderSystem.h"
#include "BaseEntity.h"
#include "World.h"
#include "../../RenderNode/RenderNode.h"
#include "../Component/RenderComponent.h"
#include "../Component/TransformComponent.h"

#include "../Singleton/CameraSingleton.h"
#include "../Singleton/PerformanceSingleton.h"
#include "../Singleton/BatchRenderSingleton.h"

namespace crude {

RenderSystem::RenderSystem(World* world)
    :BaseSystem(world)
{
    
}

void RenderSystem::Init()
{
    _camera = _world->GetSingleton<CameraSingleton>(ESingleton::ST_Camera);
    _performance = _world->GetSingleton<PerformanceSingleton>(ESingleton::ST_Performance);
    _batch = _world->GetSingleton<BatchRenderSingleton>(ESingleton::ST_BatchRender);
}

void RenderSystem::OnUpdate(float deltaTime)
{
    
}

void RenderSystem::OnRender()
{
    ayy::Camera* mainCamera = _camera->GetMainCamera();
    
    
    // draw Render Node
    std::vector<BaseEntity*> entities = GetWorld()->QueryEntities({ECompType::Render,ECompType::Transform});
    for(auto it : entities)
    {
        RenderComponent* renderComp = dynamic_cast<RenderComponent*>(it->GetComp(ECompType::Render));
        RenderNode* node = renderComp->_renderNode;
        
        auto transformComp = dynamic_cast<TransformComponent*>(it->GetComp(ECompType::Transform));
        node->ApplyRenderState();
        node->OnDraw(mainCamera,transformComp->GetWorldMatrix());
        _performance->AddDrawCall();
    }
    
    // draw batch node
    ayy::Mat4x4f idMat;
    idMat.Identify();
    for(auto it : _batch->_batchMap)
    {
        RenderNode* renderNode = it.second;
        renderNode->OnDraw(mainCamera,&idMat);
        _performance->AddDrawCall();
    }
    
    
    // draw model node
//    entities = GetWorld()->QueryEntities({ECompType::Model,ECompType::Transform});
//    for(auto it : entities)
//    {
//        auto transformComp = dynamic_cast<TransformComponent*>(it->GetComp(ECompType::Transform));
//
////        _performance
//    }
}

void RenderSystem::Cleanup()
{
    
}

}
