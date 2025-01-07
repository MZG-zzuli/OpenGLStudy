#include "material/material.h"

Material::Material()
{
}

Material::~Material()
{
}

MaterialType Material::getMaterialType() const
{
    return type_;
}
