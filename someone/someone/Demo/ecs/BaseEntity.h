#pragma once

#include "Define.h"
#include <set>
#include <map>
#include "BaseComponent.h"

namespace crude {
class BaseEntity
{
public:
    BaseEntity(EntityID uuid);
    ~BaseEntity();
    
    EntityID GetUUID() const { return _uuid;}
    
    template<typename ComponentClass>
    ComponentClass* AddComponent(ECompType compType)
    {
        auto it = _compMap.find(compType);
        if(it == _compMap.end())
        {
            auto component = new ComponentClass();
            _compMap.insert(std::make_pair(compType,(crude::BaseComponent*)component));
            return component;
        }
        return nullptr;
    }
    
    void RemoveComp(ECompType compType);
    BaseComponent* GetComp(ECompType compType);
    
    bool QueryComp(const std::vector<ECompType>& comps);
    bool CheckCompType(ECompType compType);
    
protected:
    EntityID    _uuid;
    std::map<ECompType,BaseComponent*> _compMap;
};
}

