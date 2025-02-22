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

bool Material::getEnableDepthTest() const
{
    return enable_depth_test_;
}

void Material::setEnableDepthTest(bool enable_depth_test)
{
    enable_depth_test_ = enable_depth_test;
}

GLboolean Material::getEnableDepthMask() const
{
    return enable_depth_mask_;
}

void Material::setEnableDepthMask(GLboolean enable_depth_mask)
{
    enable_depth_mask_ = enable_depth_mask;
}

GLenum Material::getDepthFunc() const
{
    return depth_func_;
}

void Material::setDepthFunc(GLenum func)
{
    depth_func_ = func;
}

bool Material::getEnablePolygonOffset() const
{
    return enable_polygon_offset_;
}

void Material::setEnablePolygonOffset(bool enable_polygon_offset)
{
    enable_polygon_offset_ = enable_polygon_offset;
}

GLenum Material::getPolygonOffsetType() const
{
    return polygon_offset_type_;
}

void Material::setPolygonOffsetType(GLenum polygon_offset_type)
{
    polygon_offset_type_ = polygon_offset_type;
}

GLfloat Material::getPolygonOffsetFactor() const
{
    return polygon_offset_factor_;
}

void Material::setPolygonOffsetFactor(GLfloat polygon_offset_factor)
{
    polygon_offset_factor_ = polygon_offset_factor;
}

GLfloat Material::getPolygonOffsetUnits() const
{
    return polygon_offset_units_;
}

void Material::setPolygonOffsetUnits(GLfloat polygon_offset_units)
{
    polygon_offset_units_ = polygon_offset_units;
}
