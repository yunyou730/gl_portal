#include "../../headers/ModelImporter/ModelImporter.h"
#include "AYYUtil.h"

#include <iostream>

namespace ayy {

namespace meshv2 {


Model* ModelImporter::CreateModel()
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("res/demo/anim_fbx/untitled.dae",aiProcess_Triangulate);
    
    if (scene == nullptr ||
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }
    
    printf("numMeshes:%d\n",scene->mNumMeshes);
    printf("numAnimations:%d\n",scene->mNumAnimations);
    
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    Bone skeleton;
    unsigned int boneCount = 0;
    loadModel(scene,vertices,indices,skeleton,boneCount);
    
    Animation animation;
    loadAnimation(scene,animation);
    
    Model* model = new Model();
    model->CreateVAO(vertices,indices);
    
    return model;
}

void ModelImporter::loadModel(const aiScene* scene,
               std::vector<Vertex>& verticesOutput,
               std::vector<uint>& indicesOutput,
               Bone& skeletonOutput,
               uint& nBoneCount)
{
    if(scene->mNumMeshes < 1)
    {
        printf("no mesh in scene\n");
        return;
    }
        
    aiMesh* mesh = scene->mMeshes[0];
    
    verticesOutput.clear();
    indicesOutput.clear();
    
    // load vertices
    for(int i = 0;i < mesh->mNumVertices;i++)
    {
        Vertex vertex;
        vertex.position = ayy::Vec3f(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);
        vertex.normal = ayy::Vec3f(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);
        vertex.uv = ayy::Vec2f(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
        
        verticesOutput.push_back(vertex);
    }
    
    // load bones
    BoneInfo boneInfo;
    nBoneCount = mesh->mNumBones;
    
    printf("nBoneCount:%d\n",nBoneCount);
    
    // all bone info
    for(int i = 0;i < nBoneCount;i++)
    {
        aiBone* bone = mesh->mBones[i];
        
        ayy::Mat4x4f offsetMatrix;
        ayy::Util::AssimpToAyyMatrix(bone->mOffsetMatrix,offsetMatrix);
        
        boneInfo[bone->mName.C_Str()] = {i,offsetMatrix};
        
        // bone weight to vertex
        for(int j = 0;j < bone->mNumWeights;j++)
        {
            uint vertexId = bone->mWeights[j].mVertexId;
            float weight = bone->mWeights[j].mWeight;
            verticesOutput[vertexId].boneIds.push_back(i);
            verticesOutput[vertexId].boneWeights.push_back(weight);
        }
    }
    
    // normalize wiehgts to make all weights sum 1
    for(int i = 0;i < verticesOutput.size();i++)
    {
        
    }
    
    // load indices
    for(int i = 0;i < mesh->mNumFaces;i++)
    {
        aiFace& face = mesh->mFaces[i];
        for(int j = 0;j < face.mNumIndices;j++)
        {
            indicesOutput.push_back(face.mIndices[j]);
        }
    }
    
    // create bone hirerchy
    readSkeleton(skeletonOutput,scene->mRootNode,boneInfo);
    
    return;
}

bool ModelImporter::readSkeleton(Bone& boneOutput,aiNode* node,BoneInfo& boneInfoTable)
{
    if(boneInfoTable.find(node->mName.C_Str()) != boneInfoTable.end())
    {
        boneOutput.name = node->mName.C_Str();
        boneOutput.boneId = boneInfoTable[boneOutput.name].first;
        boneOutput.offset = boneInfoTable[boneOutput.name].second;
        
        printf("read skeleton() bone = %s\n",boneOutput.name.c_str());
        
        for(int i = 0;i < node->mNumChildren;i++)
        {
            Bone child;
            readSkeleton(child,node->mChildren[i],boneInfoTable);
            boneOutput.children.push_back(child);
        }
        return true;
    }
    else
    {
        for(int i = 0;i < node->mNumChildren;i++)
        {
            if(readSkeleton(boneOutput,node->mChildren[i],boneInfoTable))
            {
                return true;
            }
        }
    }
    
    return false;
}

void ModelImporter::loadAnimation(const aiScene* scene,Animation& animation)
{
//    if(scene->mNumAnimations == 0)
//    {
//        return;
//    }
    
    aiAnimation* anim = scene->mAnimations[0];
    
    // animation fps
    if(anim->mTicksPerSecond != 0.0f)
    {
        animation.ticksPerSecond = anim->mTicksPerSecond;
    }
    else
    {
        animation.ticksPerSecond = 1;
    }
    
    animation.duration = anim->mDuration * anim->mTicksPerSecond;
    animation.boneTransforms = {};
    
    
    std::cout << "loadAnimation() ticksPerSecond=" << animation.ticksPerSecond << " duration=" << animation.duration << "\n" << std::endl;

    bool checkAssimpFbx = false;
    std::string assimpFbxStr;
    std::vector<BoneTransformTrack> assimpFbxVector;
    
    // load positions, rotations,scales for each bone
    // each channel represents each bone
    for(int i = 0;i < anim->mNumChannels;i++)
    {
        aiNodeAnim* channel = anim->mChannels[i];
        BoneTransformTrack track;
        
        for(int j = 0;j < channel->mNumPositionKeys;j++)
        {
            track.positionTimeStamps.push_back(channel->mPositionKeys[j].mTime);
            track.positions.push_back(ayy::Util::AssimpToAyyVec3(channel->mPositionKeys[j].mValue));
        }
        
        for(int j = 0;j < channel->mNumRotationKeys;j++)
        {
            track.rotationTimeStamps.push_back(channel->mRotationKeys[j].mTime);
            track.rotations.push_back(ayy::Util::AssimpToAyyQuat(channel->mRotationKeys[j].mValue));
        }
        
        for(int j = 0;j < channel->mNumScalingKeys;j++)
        {
            track.scaleTimeStamps.push_back(channel->mScalingKeys[j].mTime);
            track.scales.push_back(ayy::Util::AssimpToAyyVec3(channel->mScalingKeys[j].mValue));
        }
        
        // for what?
        std::string nName(channel->mNodeName.C_Str());
        std::string::size_type ret = nName.find("_$AssimpFbx$_");
        if(ret != std::string::npos)
        {
            assimpFbxStr = nName.substr(0, ret);
            assimpFbxVector.push_back(track);
            std::cout << "loadAnimation() print assimpFbxStr=" << assimpFbxStr << " OldStr=" << nName << std::endl;
        }
        else
        {
            if (checkAssimpFbx)
            {
                checkAssimpFbx = false;
                
                BoneTransformTrack outTrack;
                for (int i = 0; i < assimpFbxVector.size(); i++)
                {
                    BoneTransformTrack item = assimpFbxVector[i];
                    if (item.positions.size() > 1)
                    {
                        outTrack.positionTimeStamps = item.positionTimeStamps;
                        outTrack.positions = item.positions;
                    }
                    if (item.rotations.size() > 1)
                    {
                        outTrack.rotationTimeStamps = item.rotationTimeStamps;
                        outTrack.rotations = item.rotations;
                    }
                    if (item.scales.size() > 1)
                    {
                        outTrack.scaleTimeStamps = item.scaleTimeStamps;
                        outTrack.scales = item.scales;
                    }
                }
                std::cout << "loadAnimation() animation FBX=" << assimpFbxStr << std::endl;
                animation.boneTransforms[assimpFbxStr] = outTrack;
            }
            
            std::cout << "loadAnimation() animation=" << channel->mNodeName.C_Str() << std::endl;
            animation.boneTransforms[channel->mNodeName.C_Str()] = track;
        }
    }
}


Model::~Model()
{
    
}

void Model::CreateVAO(std::vector<Vertex>& vertices,std::vector<unsigned int> indices)
{
    // gen
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);
    
    // fill data
    glBindVertexArray(_vao);
    {
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        
        // attributes
        {
            // attribute position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
            
            // attribute normal
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
            
            // attribute uv
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
            
            // attribute boneIds
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, boneIds));
            
            // attribute boneWeights
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, boneWeights));
        }

        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(uint),&indices[0],GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
    
    
    _indiceCount = indices.size();
}


void Model::DoDraw()
{
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, (GLsizei)_indiceCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


}
}

