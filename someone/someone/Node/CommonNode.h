#pragma once
#include "Node.h"
#include <vector>
#include "../../ayy/headers/Ayy.h"

namespace ayy
{
class ShaderProgram;
class Texture;
class AYYMesh;
}

class CommonNode : public Node
{
public:
    CommonNode();
    virtual ~CommonNode();
    
    virtual void OnCreate() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnCleanUp() override;
        
    virtual void OnRender(ayy::Camera* mainCam) override;
    
    virtual void SetShader(ayy::ShaderProgram* shader);
    ayy::ShaderProgram* GetShader() { return _shader;}
    
    void SetMesh(ayy::AYYMesh* mesh);
    void AddTex(ayy::TextureUUID texId);
    
    void SetPosition(const ayy::Vec3f& pos);
    void SetPosition(float x,float y,float z);
//    void SetRotation(float rx,float ry,float rz);
    void SetRotation(float deg);
    void SetRotAxis(const ayy::Vec3f& axis);
    void SetScale(const ayy::Vec3f scale);
    void SetScale(float scale);
    
    const ayy::Vec3f& GetPosition() const {return _pos;}
//    const ayy::Vec3f& GetRotation() {return _rot;}
    const float GetRotation() const {return _rot;}
    
protected:
    virtual void SyncPropToShader(ayy::Camera* mainCam);
    
protected:
    ayy::ShaderProgram*  _shader = nullptr;
    std::vector<ayy::TextureUUID> _texIDs;
    ayy::AYYMesh* _mesh = nullptr;
    
    ayy::Vec3f  _pos;
//    ayy::Vec3f  _rot;
    float   _rot = 0.0f;
    ayy::Vec3f  _scale;
    ayy::Vec3f  _rotAxis;
};
