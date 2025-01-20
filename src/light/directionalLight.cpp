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
