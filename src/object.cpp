#include"object.h"

Object::Object()
{
	type_ = ObjectType::Object;
}

Object::~Object()
{
}

ObjectType Object::getObjectType() const
{
	return type_;
}

void Object::setPosition(QVector3D position)
{
	position_ = position;
}

QVector3D Object::getPosition() const
{
	return position_;
}

void Object::setAngle(QVector3D angle)
{
	angle_x_ = angle.x();
	angle_y_ = angle.y();
	angle_z_ = angle.z();
}

void Object::setAngleX(GLfloat angle)
{
	angle_x_ = angle;
}

GLfloat Object::getAngleX() const
{
	return angle_x_;
}

void Object::setAngleY(GLfloat angle)
{
	angle_y_ = angle;
}

GLfloat Object::getAngleY() const
{
	return angle_y_;
}

void Object::setAngleZ(GLfloat angle)
{
	angle_z_ = angle;
}

GLfloat Object::getAngleZ() const
{
	return angle_z_;
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

QVector3D Object::getScale() const
{
	return scale_;
}

QMatrix4x4 Object::getModelMatrix()
{
	QMatrix4x4 parentMatrix;
	if (parent_.lock() != nullptr)
	{
		parentMatrix=parent_.lock()->getModelMatrix();
	}
	//缩放->旋转->平移
	QMatrix4x4 modelMatrix;
	modelMatrix.scale(scale_);

	modelMatrix.rotate(angle_x_, QVector3D(1, 0, 0));
	modelMatrix.rotate(angle_y_, QVector3D(0, 1, 0));
	modelMatrix.rotate(angle_z_, QVector3D(0, 0, 1));

	modelMatrix.translate(position_);
	return parentMatrix * modelMatrix;
	
}

QMatrix3x3 Object::getNormalMatrix()
{
	return getModelMatrix().inverted().transposed().normalMatrix();
}

std::shared_ptr<Object> Object::getParent() const
{
	return parent_.lock();
}

void Object::setParent(std::shared_ptr<Object> parent)
{
	auto i = this;
	parent_ = parent;
}

std::set<std::shared_ptr<Object>>& Object::getChildrens()
{
	return childrens_;
}

void Object::addChild(std::shared_ptr<Object> child)
{
	childrens_.insert(child);
	child->setParent(shared_from_this());
}
