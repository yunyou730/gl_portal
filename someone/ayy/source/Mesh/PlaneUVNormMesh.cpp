#include "../../headers/Mesh/PlaneUVNormMesh.h"

namespace ayy {
PlaneUVNormMesh::PlaneUVNormMesh()
{
    
}

PlaneUVNormMesh::~PlaneUVNormMesh()
{
    
}

void PlaneUVNormMesh::Prepare()
{
    CalcTBN();
    
    float vertices[] = {
        // up left
        _pos1.x(),_pos1.y(),_pos1.z(),
        _uv1.x(),_uv1.y(),
        _nm.x(),_nm.y(),_nm.z(),
        _tangent1.x(),_tangent1.y(),_tangent1.z(),
        _bitangent1.x(),_bitangent1.y(),_bitangent1.z(),
                
        // down left
        _pos2.x(),_pos2.y(),_pos2.z(),
        _uv2.x(),_uv2.y(),
        _nm.x(),_nm.y(),_nm.z(),
        _tangent1.x(),_tangent1.y(),_tangent1.z(),
        _bitangent1.x(),_bitangent1.y(),_bitangent1.z(),
                
        // down right
        _pos3.x(),_pos3.y(),_pos3.z(),
        _uv3.x(),_uv3.y(),
        _nm.x(),_nm.y(),_nm.z(),
        _tangent1.x(),_tangent1.y(),_tangent1.z(),
        _bitangent1.x(),_bitangent1.y(),_bitangent1.z(),
        
        
        
        // up left
        _pos1.x(),_pos1.y(),_pos1.z(),
        _uv1.x(),_uv1.y(),
        _nm.x(),_nm.y(),_nm.z(),
        _tangent2.x(),_tangent2.y(),_tangent2.z(),
        _bitangent2.x(),_bitangent2.y(),_bitangent2.z(),
        
        // down right
        _pos3.x(),_pos3.y(),_pos3.z(),
        _uv3.x(),_uv3.y(),
        _nm.x(),_nm.y(),_nm.z(),
        _tangent2.x(),_tangent2.y(),_tangent2.z(),
        _bitangent2.x(),_bitangent2.y(),_bitangent2.z(),
                
        // up right
        _pos4.x(),_pos4.y(),_pos4.z(),
        _uv4.x(),_uv4.y(),
        _nm.x(),_nm.y(),_nm.z(),
        _tangent2.x(),_tangent2.y(),_tangent2.z(),
        _bitangent2.x(),_bitangent2.y(),_bitangent2.z(),
    };
    
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
//    glGenBuffers(1,&_ebo);
    
    glBindVertexArray(_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            
            // pos 0 , attribute pos
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 14 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            // pos 1 , uv 
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            
            // pos 2, normal dir
            glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE, 14 * sizeof(float), (void*)(5 * sizeof(float)));
            glEnableVertexAttribArray(2);
            
            // tangent
            glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
            glEnableVertexAttribArray(3);
            
            // bitangent
            glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
            glEnableVertexAttribArray(4);
            
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    glBindVertexArray(0);
}

void PlaneUVNormMesh::Cleanup()
{
    if(_vao > 0)
    {
        glDeleteVertexArrays(1,&_vao);
        _vao = 0;
    }
    
    if(_vbo > 0)
    {
        glDeleteBuffers(1,&_vbo);
        _vbo = 0;
    }
}

void PlaneUVNormMesh::Draw()
{
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}

void PlaneUVNormMesh::Bind()
{
    glBindVertexArray(_vao);
}

void PlaneUVNormMesh::UnBind()
{
    glBindVertexArray(0);
}

int PlaneUVNormMesh::GetIndexCount()
{
    return 6;
}


static void CalcTangentAndBiTangent(const ayy::Vec3f& edge1,
                                    const ayy::Vec3f& edge2,
                                    const ayy::Vec2f& deltaUV1,
                                    const ayy::Vec2f& deltaUV2,
                                    ayy::Vec3f& tangent,
                                    ayy::Vec3f& bitangent)
{
    float f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());
    
    float tx = f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x());
    float ty = f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y());
    float tz = f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z());
    
    
    tangent.SetX(tx);
    tangent.SetY(ty);
    tangent.SetZ(tz);
    tangent.Normalize();
    
    tx = f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x());
    ty = f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y());
    tz = f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z());
    
    bitangent.SetX(tx);
    bitangent.SetY(ty);
    bitangent.SetZ(tz);
    bitangent.Normalize();
}

void PlaneUVNormMesh::CalcTBN()
{
    // calc tangent & bitangent of triangle 1
    {
        ayy::Vec3f edge1 = _pos2 - _pos1;
        ayy::Vec3f edge2 = _pos3 - _pos1;
        ayy::Vec2f deltaUV1 = _uv2 - _uv1;
        ayy::Vec2f deltaUV2 = _uv3 - _uv1;
        
        CalcTangentAndBiTangent(edge1,edge2,deltaUV1,deltaUV2,_tangent1,_bitangent1);
    }
    
    
    // calc tangent & bitangent of triangle 2
    {
        ayy::Vec3f edge1 = _pos3 - _pos1;
        ayy::Vec3f edge2 = _pos4 - _pos1;
        ayy::Vec2f deltaUV1 = _uv3 - _uv1;
        ayy::Vec2f deltaUV2 = _uv4 - _uv1;
        
        CalcTangentAndBiTangent(edge1,edge2,deltaUV1,deltaUV2,_tangent2,_bitangent2);
    }
}

}
