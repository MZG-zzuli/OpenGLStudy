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
	GLfloat getSpecularIntensity() const;				//获取镜面反射强度
	void setSpecularIntensity(GLfloat intensity);		//设置镜面反射强度
private:
	QVector3D direction_{ -1.0f, 0, -1.0f };		//平行光方向
	GLfloat specular_intensity_{ 0.5f };				//镜面反射强度


};