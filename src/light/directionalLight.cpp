#include "light/directionalLight.h"

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}

QVector3D DirectionalLight::getTargetDirection() const
{
    return target_direction_;
}

void DirectionalLight::setTargetDirection(const QVector3D& direction)
{
    target_direction_ = direction;
}
