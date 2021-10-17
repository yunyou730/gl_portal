#pragma once
#include "Ayy.h"
#include "Define.h"
#include "SingletonComponent.h"
#include <vector>
#include <map>
#include <string>

namespace crude {

class RenderNode;
class BatchRenderSingleton : public SingletonComponent
{
public:
    virtual ~BatchRenderSingleton();
    void AddBatchNode(const std::string& key,RenderNode* renderNode);
    
    bool CheckBatchExist(const std::string& key) const {
        return _batchMap.find(key) != _batchMap.end();
    }
    
    template<typename RenderNodeClass>
    RenderNodeClass* GetRenderNode(const std::string& key)
    {
        auto it = _batchMap.find(key);
        if(it == _batchMap.end())
            return nullptr;
        return dynamic_cast<RenderNodeClass*>(it->second);
    }
    
public:
    std::map<std::string,RenderNode*>   _batchMap;
};


}

