#pragma once

#include "Define.h"
#include <set>
#include <map>

namespace crude {
class BaseComponent;
class BaseEntity
{
public:
    BaseEntity(EntityID uuid);
    ~BaseEntity();
    
    EntityID GetUUID() const { return _uuid;}
    
    BaseComponent* AddComp(ECompType compType);
    void RemoveComp(ECompType compType);
    BaseComponent* GetComp(ECompType compType);
    
    bool QueryComp(const std::vector<ECompType>& comps);
    bool CheckCompType(ECompType compType);
    
protected:
    EntityID    _uuid;
    std::map<ECompType,BaseComponent*> _compMap;
};
}

