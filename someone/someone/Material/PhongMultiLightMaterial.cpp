#include "PhongMultiLightMaterial.h"

void PhongMultiLightMaterial::SetTexture(ayy::TextureUUID texDiffuse,ayy::TextureUUID texSpecular)
{
    _texDiffuse = texDiffuse;
    _texSpecular = texSpecular;
}

void PhongMultiLightMaterial::SetSpecularShininess(float shininess)
{
    _shininess = shininess;
}

void PhongMultiLightMaterial::SyncShaderParam()
{
    // object material
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texDiffuse, 0);
    ayy::TextureManager::GetInstance()->BindTextureToSlot(_texSpecular, 1);
    _shader->SetUniform("u_Material.diffuse",0);
    _shader->SetUniform("u_Material.specular",1);
    _shader->SetUniform("u_Material.shininess",_shininess);
    
    // light enable
    _shader->SetUniform("u_bEnableDirLight",_bEnableDirLight);
    _shader->SetUniform("u_bEnablePointLight",_bEnablePointLight);
    _shader->SetUniform("u_bEnableSpotLight",_bEnableSpotLight);
    
    // dir light
    _shader->SetUniform("u_DirLight.direction",_dirLightParam.direction);
    _shader->SetUniform("u_DirLight.ambient",_dirLightParam.ambient);
    _shader->SetUniform("u_DirLight.diffuse",_dirLightParam.diffuse);
    _shader->SetUniform("u_DirLight.specular",_dirLightParam.specular);
    
    // point light
    _shader->SetUniform("u_PointLight.position",_pointLightParam.position);
    _shader->SetUniform("u_PointLight.ambient",_pointLightParam.ambient);
    _shader->SetUniform("u_PointLight.diffuse",_pointLightParam.diffuse);
    _shader->SetUniform("u_PointLight.specular",_pointLightParam.specular);
    
    _shader->SetUniform("u_PointLight.constant",_pointLightParam.constant);
    _shader->SetUniform("u_PointLight.linear",_pointLightParam.linear);
    _shader->SetUniform("u_PointLight.quadratic",_pointLightParam.quadratic);
    
    // spot light
    _shader->SetUniform("u_SpotLight.position",_spotLightParam.position);
    _shader->SetUniform("u_SpotLight.direction",_spotLightParam.direction);
    _shader->SetUniform("u_SpotLight.cutOff",cos(ayy::DegToRad(_spotLightParam.deg)));
    _shader->SetUniform("u_SpotLight.outerCutOff",cos(ayy::DegToRad(_spotLightParam.outerDeg)));
    
    _shader->SetUniform("u_SpotLight.ambient",_spotLightParam.ambient);
    _shader->SetUniform("u_SpotLight.diffuse",_spotLightParam.diffuse);
    _shader->SetUniform("u_SpotLight.specular",_spotLightParam.specular);
}
