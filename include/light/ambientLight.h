#pragma once

#include"light/light.h"

class AmbientLight : public Light
{
public:
	AmbientLight();
	~AmbientLight();
	void setAmbientColor(const QVector3D& color);
private:
};