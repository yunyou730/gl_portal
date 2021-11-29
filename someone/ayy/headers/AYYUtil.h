#pragma once
#include <string>
#include "AYYMath.h"
#include "AYYQuaternion.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
    
    static void AssimpToAyyMatrix(const aiMatrix4x4& src,ayy::Mat4x4f& dest);
    static ayy::Vec3f AssimpToAyyVec3(const aiVector3D& vec);
    static ayy::Quaternion AssimpToAyyQuat(const aiQuaternion& quat);
};
}
