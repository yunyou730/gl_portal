#include "BaseEntity.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "KeyboardInputComponent.h"

namespace crude {

BaseEntity::BaseEntity(EntityID uuid)
    :_uuid(uuid)
{
    
}

BaseEntity::~BaseEntity()
{
    for(auto it : _compMap)
    {
        AYY_SAFE_DEL(it.second);
    }
    _compMap.clear();
}

//BaseComponent* BaseEntity::AddComp(ECompType compType)
//{
//    auto it = _compMap.find(compType);
//    if(it == _compMap.end())
//    {
//        BaseComponent* component = nullptr;
//        switch(compType)
//        {
//            case ECompType::Render:
//                component = new RenderComponent();
//                break;
//            case ECompType::Transform:
//                component = new TransformComponent();
//                break;
//            case ECompType::Camera:
//                component = new CameraComponent();
//                break;
//            case ECompType::KeyboardInput:
//                component = new KeyboardInputComponent();
//                break;
//            default:
//                break;
//        }
//        if(component != nullptr)
//        {
//            _compMap.insert(std::make_pair(compType,component));
//        }
//        return component;
//    }
//    return nullptr;
//}

void BaseEntity::RemoveComp(ECompType compType)
{
    
}

BaseComponent* BaseEntity::GetComp(ECompType compType)
{
    auto it = _compMap.find(compType);
    if(it != _compMap.end())
    {
        return it->second;
    }
    return nullptr;
}

bool BaseEntity::QueryComp(const std::vector<ECompType>& comps)
{
    for(auto it : comps)
    {
        if(!CheckCompType(it))
        {
            return false;
        }
    }
    return true;
}

bool BaseEntity::CheckCompType(ECompType compType)
{
    return _compMap.find(compType) != _compMap.end();
}

}
