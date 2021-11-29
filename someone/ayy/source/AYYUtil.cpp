#include "AYYUtil.h"
#include "AYYShader.h"
#include "AYYIO.h"
#include "AYYTexture.h"
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

    int Util::Rand(int min,int max)
    {
//        static bool b
        assert(max > min);
        int n = rand() % (max - min);
        return n + min;
    }
    
    void Util::AssimpToAyyMatrix(const aiMatrix4x4& src,ayy::Mat4x4f& dest)
    {
        // @miao @todo
        for(int y = 0;y < 4;y++)
        {
            for(int x = 0;x < 4;x++)
            {
                dest.Set(x,y,src[y][x]);
            }
        }
    }
    
    ayy::Vec3f Util::AssimpToAyyVec3(const aiVector3D& vec)
    {
        return ayy::Vec3f(vec.x,vec.y,vec.z);
    }
    
    ayy::Quaternion Util::AssimpToAyyQuat(const aiQuaternion& quat)
    {
        ayy::Quaternion q(quat.x,quat.y,quat.z,quat.w);
        return q;
    }
}
