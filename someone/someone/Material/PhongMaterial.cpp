#include "PhongMaterial.h"


void PhongMaterial::SyncShaderParam()
{
    _shader->SetUniform("u_Material.ambient",_ambientColor);
    glCheckError();
    _shader->SetUniform("u_Material.diffuse",_diffuseColor);
    glCheckError();
    _shader->SetUniform("u_Material.specular",_specularColor);
    glCheckError();
    _shader->SetUniform("u_Material.shininess",_shininess);
    glCheckError();
}

void PhongMaterial::SetAmbientColor(const ayy::Vec3f& color)
{
    _ambientColor = color;
}

void PhongMaterial::SetDiffuseColor(const ayy::Vec3f& color)
{
    _diffuseColor = color;
}

void PhongMaterial::SetSpecularColor(const ayy::Vec3f& color)
{
    _specularColor = color;
}

void PhongMaterial::SetSpecularShininess(float shininess)
{
    _shininess = shininess;
}
