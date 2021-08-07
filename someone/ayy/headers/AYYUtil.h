#pragma once
#include <string>

namespace ayy {

class ShaderProgram;
class Texture;
class RawTexture;

class Util
{
public:
    static ShaderProgram* CreateShaderWithFile(const std::string& vsFilePath,const std::string& fsFilePath);
    
    static RawTexture* CreateRawTextureWithFile(const std::string& filePath);
    static Texture* CreateTexturehWithFile(const std::string& filePath);
    
    
    // return [min,max)
    static int Rand(int min,int max);
};
}
