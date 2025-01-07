#include "light/ambientLight.h"

AmbientLight::AmbientLight()
{
	color_ = QVector3D(0.2f, 0.2f, 0.2f);
}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::setAmbientColor(const QVector3D& color)
{
	color_ = color;
}
