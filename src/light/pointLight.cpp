#include "light/pointLight.h"

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

void PointLight::setPosition(QVector3D position)
{
	position_ = position;
}

QVector3D PointLight::getPosition() const
{
	return position_;
}

void PointLight::setAttenuation(GLfloat k1, GLfloat k2, GLfloat kc)
{
	k1_ = k1;
	k2_ = k2;
	kc_ = kc;
}

GLfloat PointLight::getAttenuationK1() const
{
	return k1_;
}

GLfloat PointLight::getAttenuationK2() const
{
	return k2_;
}

GLfloat PointLight::getAttenuationKc() const
{
	return kc_;
}
