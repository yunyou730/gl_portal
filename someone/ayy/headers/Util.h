#pragma once
#include "IO.h"
#include <string>

namespace ayy {

class ShaderProgram;

class Util
{
public:
    static ShaderProgram* CreateShaderWithFile(const std::string& vsFilePath,const std::string& fsFilePath);
};
}
