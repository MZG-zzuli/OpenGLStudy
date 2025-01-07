#include"light/light.h"

Light::Light()
{
}

Light::~Light()
{
}

QVector3D Light::getColor() const
{
    return color_;
}
