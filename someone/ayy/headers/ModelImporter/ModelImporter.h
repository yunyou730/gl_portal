#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AYYMath.h"
#include "AYYQuaternion.h"
#include <string>
#include <vector>
#include <unordered_map>

#include <glad/glad.h>

namespace ayy {

namespace meshv2{

struct Vertex
{
    ayy::Vec3f position;
    ayy::Vec3f normal;
    ayy::Vec2f uv;
    std::vector<unsigned int>   boneIds;
    std::vector<float>          boneWeights;
};

struct Bone
{
    int boneId;
    std::string name;
    ayy::Mat4x4f offset;
    std::vector<Bone> children;
};


struct BoneTransformTrack
{
    std::vector<float> positionTimeStamps;
    std::vector<float> rotationTimeStamps;
    std::vector<float> scaleTimeStamps;
    
    std::vector<ayy::Vec3f> positions;
    std::vector<ayy::Quaternion> rotations;
    std::vector<ayy::Vec3f> scales;
};

struct Animation
{
    float duration = 0.0f;
    float ticksPerSecond = 1.0f;
    std::unordered_map<std::string,BoneTransformTrack> boneTransforms;
};

class Model;
class ModelImporter
{
    using BoneInfo = std::unordered_map<std::string,std::pair<int,ayy::Mat4x4f>>;
public:
    Model* CreateModel();
    
protected:
    void loadModel(const aiScene* scene,
                   std::vector<Vertex>& verticesOutput,
                   std::vector<uint>& indicesOutput,
                   Bone& skeletonOutput,
                   uint& nBoneCount);
    
    bool readSkeleton(Bone& boneOutput,
                      aiNode* node,
                      BoneInfo& boneInfoTable);
    
    void loadAnimation(const aiScene* scene,Animation& animation);
};

class Model
{
public:
    ~Model();
    void CreateVAO(std::vector<Vertex>& vertices,std::vector<unsigned int> indices);
    void DoDraw();
    
protected:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    
    unsigned int _indiceCount = 0;
};

}
}
