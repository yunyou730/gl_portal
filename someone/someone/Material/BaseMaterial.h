#pragma once
#include "../../ayy/headers/Ayy.h"

class BaseMaterial
{
public:
    virtual void SyncShaderParam() = 0;
    void SetShader(ayy::ShaderProgram* shader) {_shader = shader;}
    ayy::ShaderProgram* GetShader() { return _shader;}
protected:
    ayy::ShaderProgram*    _shader = nullptr;
};
