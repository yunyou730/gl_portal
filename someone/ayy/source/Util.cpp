#include "../headers/Util.h"
#include "Shader.h"
#include "IO.h"

namespace ayy {
    ShaderProgram* Util::CreateShaderWithFile(const std::string& vsFilePath,const std::string& fsFilePath)
    {
        std::string vsCode,fsCode;
        ayy::ReadFile(vsFilePath,vsCode);
        ayy::ReadFile(fsFilePath,fsCode);
        auto shader = ShaderProgram::CreateShaderProgram(vsCode,fsCode);
        return shader;
    }
}
