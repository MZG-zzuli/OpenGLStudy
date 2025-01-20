#pragma once
#include"light/light.h"
#include<QtMath>
//探照灯
class SpotLight : public Light
{
public:
	SpotLight();
	~SpotLight();
	void setPosition(const QVector3D& position);
	QVector3D getPosition() const;
	void setTargetDirection(const QVector3D& target_direction);
	QVector3D getTargetDirection() const;
	void setInnerAngle(GLfloat inner_angle);
	GLfloat getInnerAngle() const;
	void setOuterAngle(GLfloat outer_angle);
	GLfloat getOuterAngle() const;
private:
	QVector3D position_;
	QVector3D target_direction_{ -1,0,0 };
	GLfloat inner_angle_{ M_PI / 9 };
	GLfloat outer_angle_{ M_PI / 6 };
};