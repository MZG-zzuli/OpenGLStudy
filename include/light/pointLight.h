#pragma once
#include"light/light.h"
#include<QOpenGLWidget>
#include<memory>
class PointLight :public Light
{
public:
	PointLight();
	~PointLight();
	void setPosition(QVector3D position);
	QVector3D getPosition() const;
	void setAttenuation(GLfloat k1, GLfloat k2, GLfloat kc);
	GLfloat getAttenuationK1() const;
	GLfloat getAttenuationK2() const;
	GLfloat getAttenuationKc() const;
private:
	QVector3D position_;		//点光源位置
	GLfloat k1_ = 0.07;			//缩减系数1
	GLfloat k2_ = 0.017;			//缩减系数2
	GLfloat kc_ = 1;			//常数项

};