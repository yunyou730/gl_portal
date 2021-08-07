#include "ModelNode.h"
#include "../../ayy/headers/ModelImporter/Model.h"
#include "PhongMultiLightMaterial.h"

ModelNode::ModelNode(const std::string& modelPath,const std::string& modelPrefixPath)
    :CommonNode()
{
    _model = new ayy::model::Model();
    _model->Load(modelPath, modelPrefixPath);
    
//    _material = new PhongMultiLightMaterial();
}

ModelNode::~ModelNode()
{
    AYY_SAFE_DEL(_model);
//    AYY_SAFE_DEL(_material);
}

void ModelNode::OnRender(ayy::Camera* mainCam)
{
    CommonNode::OnRender(mainCam);
    _model->Draw(_shader);
}

void ModelNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    
    _shader->SetUniform("u_ViewPos",mainCam->GetPos());
    _shader->SetUniform("material.shininess",_shininess);
    
    _shader->SetUniform("u_DirectionLight.direction",_dirLight.direction);
    _shader->SetUniform("u_DirectionLight.ambient",_dirLight.ambient);
    _shader->SetUniform("u_DirectionLight.diffuse",_dirLight.diffuse);
    _shader->SetUniform("u_DirectionLight.specular",_dirLight.specular);

    _shader->SetUniform("u_PointLight.position",_pointLight.position);
    _shader->SetUniform("u_PointLight.ambient",_pointLight.ambient);
    _shader->SetUniform("u_PointLight.diffuse",_pointLight.diffuse);
    _shader->SetUniform("u_PointLight.specular",_pointLight.specular);
    _shader->SetUniform("u_PointLight.constant",_pointLight.constant);
    _shader->SetUniform("u_PointLight.linear",_pointLight.linear);
    _shader->SetUniform("u_PointLight.quadratic",_pointLight.quadratic);
    
    _shader->SetUniform("u_SpotLight.position",_spotLight.position);
    _shader->SetUniform("u_SpotLight.direction",_spotLight.direction);
    _shader->SetUniform("u_SpotLight.cutOff",cos(ayy::DegToRad(_spotLight.deg)));
    _shader->SetUniform("u_SpotLight.outerCutOff",cos(ayy::DegToRad(_spotLight.outerDeg)));
    _shader->SetUniform("u_SpotLight.ambient",_spotLight.ambient);
    _shader->SetUniform("u_SpotLight.diffuse",_spotLight.diffuse);
    _shader->SetUniform("u_SpotLight.specular",_spotLight.specular);
    
    _shader->SetUniform("u_bEnableDirLight",_bEnableDirLight);
    _shader->SetUniform("u_bEnablePointLight",_bEnablePointLight);
    _shader->SetUniform("u_bEnableSpotLight",_bEnableSpotLight);
}

void ModelNode::SetDirLight(const DirectionLight& dirLight)
{
    _dirLight = dirLight;
}

void ModelNode::SetPointLight(const PointLight& pointLight)
{
    _pointLight = pointLight;
}

void ModelNode::SetSpotLight(const SpotLight& spotLight)
{
    _spotLight = spotLight;
}

void ModelNode::SetShininess(float shininess)
{
    _shininess = shininess;
}
