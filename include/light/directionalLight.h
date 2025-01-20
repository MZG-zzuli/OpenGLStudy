#pragma once
#include"light/light.h"

//平行光
class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();
	QVector3D getDirection() const;						//获取光源方向
	void setDirection(const QVector3D& direction);		//设置光源方向
private:
	QVector3D direction_{ -1.0f, 0, -1.0f };		//平行光方向


};