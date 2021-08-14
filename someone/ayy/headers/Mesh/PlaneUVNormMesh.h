#pragma once
#include "AYYMesh.h"
#include "AYYMath.h"

namespace ayy {
class PlaneUVNormMesh : public AYYMesh
{
public:
    PlaneUVNormMesh();
    virtual ~PlaneUVNormMesh();
    
    virtual void Prepare() override;
    virtual void Cleanup() override;
    virtual void Draw() override;
    
    void Bind() override;
    void UnBind() override;
    
    virtual int GetIndexCount() override;
protected:
    void CalcTBN();
    
protected:
    GLuint  _vao,_vbo;
    
    // vertices
    ayy::Vec3f _pos1 = ayy::Vec3f(-1, 1, 0);
    ayy::Vec3f _pos2 = ayy::Vec3f(-1,-1, 0);
    ayy::Vec3f _pos3 = ayy::Vec3f( 1,-1, 0);
    ayy::Vec3f _pos4 = ayy::Vec3f( 1, 1, 0);
    
    // UVs
    ayy::Vec2f _uv1 = ayy::Vec2f(0.0,1.0);
    ayy::Vec2f _uv2 = ayy::Vec2f(0.0,0.0);
    ayy::Vec2f _uv3 = ayy::Vec2f(1.0,0.0);
    ayy::Vec2f _uv4 = ayy::Vec2f(1.0,1.0);
    
    // normal
    ayy::Vec3f _nm = ayy::Vec3f(0.0,0.0,1.0);
    
    ayy::Vec3f  _tangent1;
    ayy::Vec3f  _tangent2;
    ayy::Vec3f  _bitangent1;
    ayy::Vec3f  _bitangent2;
};

}
