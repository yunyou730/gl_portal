#include "BatchRenderSingleton.h"
#include "Util.h"
#include "../../RenderNode/RenderNode.h"

namespace crude
{
BatchRenderSingleton::~BatchRenderSingleton()
{
    for(auto it : _batchMap)
    {
        AYY_SAFE_DEL(it.second);
    }
    _batchMap.clear();
}

void BatchRenderSingleton::AddBatchNode(const std::string& key,RenderNode* renderNode)
{
    auto it = _batchMap.find(key);
    if(it == _batchMap.end())
    {
        _batchMap.insert(std::make_pair(key,renderNode));
    }
}

}
