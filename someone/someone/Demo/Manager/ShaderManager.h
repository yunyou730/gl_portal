#pragma once
#include "Ayy.h"
#include "BaseManager.h"
#include <string>
#include <map>

namespace crude
{
class ShaderManager : public BaseManager
{
    friend class BaseManager;
public:
    virtual ~ShaderManager();
    virtual void Initialize() override;
    
    ayy::ShaderProgram* LoadProgram(const std::string& vsfile,const std::string& fsfile);
    
    
protected:
    ShaderManager();
    
protected:
    std::map<std::string,ayy::ShaderProgram*>   _shaderMap;
};

}
