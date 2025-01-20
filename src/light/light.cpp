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

GLfloat Light::getSpecularIntensity() const
{
    return specular_intensity_;
}

void Light::setSpecularIntensity(GLfloat intensity)
{
    specular_intensity_ = intensity;
}
