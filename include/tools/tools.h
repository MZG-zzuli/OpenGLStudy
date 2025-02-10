#pragma once
#include<QVector3D>
#include<QMatrix4x4>

class Tools
{
public:
	//获取位置
	static QVector3D getPosition(QMatrix4x4& matrix);
	//获取旋转角度
	static QVector3D getEulerAngle(QMatrix4x4& matrix);
	//获取缩放因子
	static QVector3D getScale(QMatrix4x4& matrix);
};