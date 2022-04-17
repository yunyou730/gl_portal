#include <glad/glad.h>
#include <map>
#include <string>

namespace ayy
{

class BuiltinMesh
{
public:
    unsigned int vao,vbo,ebo;
    std::string refVS;
    std::string refFS;
};

class BuiltinMeshFactory
{
public:
    void Init();
    void Cleanup();
    
    BuiltinMesh* GetBuiltinMesh(const std::string& virtualPath);
    
protected:
    BuiltinMesh* CreateQuad();
    BuiltinMesh* CreateCube();
    
protected:
    std::map<std::string,BuiltinMesh*>  _builtinMeshes;
};

}
