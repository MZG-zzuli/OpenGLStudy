#include"tools/tools.h"
#include<QQuaternion>


QVector3D Tools::getPosition(QMatrix4x4& matrix)
{
	return matrix.column(3).toVector3D();
}

QVector3D Tools::getEulerAngle(QMatrix4x4& matrix)
{
	QQuaternion quaternion;
	matrix.rotate(quaternion);
	return quaternion.toEulerAngles();
}

QVector3D Tools::getScale(QMatrix4x4& matrix)
{
	QVector3D scale;
	//012列对应x,y,z方向的单位向量，其长度就是缩放倍数
	scale.setX(matrix.column(0).length());
	scale.setY(matrix.column(1).length());
	scale.setZ(matrix.column(2).length());
	return scale;
}
