#include"light/spotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::setPosition(const QVector3D& position)
{
	position_ = position;
}

QVector3D SpotLight::getPosition() const
{
	return position_;
}

void SpotLight::setTargetDirection(const QVector3D& target_direction)
{
	target_direction_ = target_direction;
}

QVector3D SpotLight::getTargetDirection() const
{
	return target_direction_;
}

void SpotLight::setInnerAngle(GLfloat inner_angle)
{
	inner_angle_ = inner_angle;
}

GLfloat SpotLight::getInnerAngle() const
{
	return inner_angle_;
}

void SpotLight::setOuterAngle(GLfloat outer_angle)
{
	outer_angle_ = outer_angle;
}

GLfloat SpotLight::getOuterAngle() const
{
	return outer_angle_;
}
