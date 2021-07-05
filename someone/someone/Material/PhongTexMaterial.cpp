#include "PhongTexMaterial.h"


void PhongTexMaterial::SyncShaderParam()
{
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texDiffuse, 0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texSpecular, 1);
    
    _shader->SetUniform("u_Material.diffuse",0);
    glCheckError();
    _shader->SetUniform("u_Material.specular",1);
    glCheckError();
    _shader->SetUniform("u_Material.shininess",_shininess);
    glCheckError();
}
