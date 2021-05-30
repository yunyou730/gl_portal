#pragma once
#include "IO.h"
#include <string>

namespace ayy {

class ShaderProgram;
class Texture;

class Util
{
public:
    static ShaderProgram* CreateShaderWithFile(const std::string& vsFilePath,const std::string& fsFilePath);
    
    static Texture* CreateTexturehWithFile(const std::string& filePath);
};
}
