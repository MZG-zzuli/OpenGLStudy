#pragma once

#include<mutex>
#include<QOpenGLShaderProgram>
enum class MaterialType
{
    PhongMaterial,
    WhiteMaterial
};

class Material
{
public:
    Material();
    virtual ~Material();
    MaterialType getMaterialType() const;
protected:
    MaterialType type_;
};