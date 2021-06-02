#include "../headers/Util.h"
#include "Shader.h"
#include "IO.h"
#include "Texture.h"
#include "stb_image.h"

namespace ayy {
    ShaderProgram* Util::CreateShaderWithFile(const std::string& vsFilePath,const std::string& fsFilePath)
    {
        std::string vsCode,fsCode;
        ayy::ReadFile(vsFilePath,vsCode);
        ayy::ReadFile(fsFilePath,fsCode);
        auto shader = ShaderProgram::CreateShaderProgram(vsCode,fsCode);
        return shader;
    }
    


    Texture* Util::CreateTexturehWithFile(const std::string& filePath)
    {
        /*
        int width = 0;
        int height = 0;
        int channels = 0;
        unsigned char* data = nullptr;
        */
        
//        Texture::RawTexture t;
        RawTexture* rawTex = nullptr;
        
        
         
        return nullptr;
    }
}
