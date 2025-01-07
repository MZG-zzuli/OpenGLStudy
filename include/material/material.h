#pragma once

enum class MaterialType
{
    PhongMaterial
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