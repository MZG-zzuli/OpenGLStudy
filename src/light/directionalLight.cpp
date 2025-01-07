#include "light/directionalLight.h"

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}

QVector3D DirectionalLight::getDirection() const
{
    return direction_;
}

void DirectionalLight::setDirection(const QVector3D& direction)
{
    direction_ = direction;
}

GLfloat DirectionalLight::getSpecularIntensity() const
{
    return specular_intensity_;
}

void DirectionalLight::setSpecularIntensity(GLfloat intensity)
{
    specular_intensity_ = intensity;
}
