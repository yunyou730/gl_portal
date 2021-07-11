#include "ModelNode.h"
#include "../../ayy/headers/ModelImporter/Model.h"

ModelNode::ModelNode(const std::string& modelPath,const std::string& modelPrefixPath)
    :CommonNode()
{
    _model = new ayy::model::Model();
    _model->Load(modelPath, modelPrefixPath);
}

ModelNode::~ModelNode()
{
    AYY_SAFE_DEL(_model);
}

void ModelNode::OnRender(ayy::Camera* mainCam)
{
    CommonNode::OnRender(mainCam);
    _model->Draw(_shader,mainCam);
}

void ModelNode::SyncPropToShader(ayy::Camera* mainCam)
{
    CommonNode::SyncPropToShader(mainCam);
    
    // @miao @todo
}
