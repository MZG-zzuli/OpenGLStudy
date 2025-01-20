#include"object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::setPosition(QVector3D position)
{
	position_ = position;
}

QVector3D Object::getPosition() const
{
	return position_;
}

void Object::rotateX(float angle)
{
	angle_x_ += angle;
}

void Object::rotateY(float angle)
{
	angle_y_ += angle;
}

void Object::rotateZ(float angle)
{
	angle_z_ += angle;
}

void Object::setScale(QVector3D scale)
{
	scale_ = scale;
}

QMatrix4x4 Object::getModelMatrix()
{
	//缩放->旋转->平移
	QMatrix4x4 modelMatrix;
	modelMatrix.scale(scale_);
	modelMatrix.rotate(angle_x_, QVector3D(1, 0, 0));
	modelMatrix.rotate(angle_y_, QVector3D(0, 1, 0));
	modelMatrix.rotate(angle_z_, QVector3D(0, 0, 1));
	modelMatrix.translate(position_);
	return modelMatrix;
	
}

QMatrix3x3 Object::getNormalMatrix()
{
	return getModelMatrix().inverted().transposed().normalMatrix();
}
