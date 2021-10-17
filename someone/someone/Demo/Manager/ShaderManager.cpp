#include "ShaderManager.h"

namespace crude
{

ShaderManager::ShaderManager()
{
    
}

ShaderManager::~ShaderManager()
{
    for(auto it : _shaderMap)
    {
        AYY_SAFE_DEL(it.second);
    }
    _shaderMap.clear();
}

void ShaderManager::Initialize()
{
    
}


ayy::ShaderProgram* ShaderManager::LoadProgram(const std::string& vsfile,const std::string& fsfile)
{
    const std::string key = vsfile + "_" + fsfile;
    auto it = _shaderMap.find(key);
    if(it == _shaderMap.end())
    {
        auto program = ayy::Util::CreateShaderWithFile(vsfile,fsfile);
        _shaderMap.insert(std::make_pair(key,program));
        return program;
    }
    return it->second;
}

}
