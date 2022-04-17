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

extern const int kVertMaxBones;
extern const int kMeshMaxBones;

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
    void SetSkeleton(Bone* skeleton,unsigned int boneCount);
    void SetAnimation(Animation* animation);
    
    void DoDraw();
    
    unsigned int GetBoneCount() const { return _boneCount;}
    
    
    void InitPose();
    const std::vector<ayy::Mat4x4f>& GetPose();
    void CalcPose(float animPct);
    
protected:
    // mesh
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    unsigned int _indiceCount = 0;
    
    // skeleton
    Bone* _skeleton = nullptr;
    unsigned int _boneCount = 0;
    
    // animation
    Animation* _animation = nullptr;
    
    // pose data,saved as matrix
    std::vector<ayy::Mat4x4f>   _pose;
};

void getPose(const Animation& animation,
             const Bone& skeletion,
             float dt,
             std::vector<ayy::Mat4x4f>& output,
             ayy::Mat4x4f& parentTransform,
             ayy::Mat4x4f& globalInverseTransform);

}
}
