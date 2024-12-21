#include "Camera.h"
Camera::Camera()
{
}

Camera::~Camera()
{
}

QMatrix4x4 Camera::getViewMatrix()
{
	QVector3D front = QVector3D::crossProduct(mUp_, mRight_);
	QVector3D center= mPosition_ + front;
	QMatrix4x4 viewMatrix;
	viewMatrix.lookAt(mPosition_, center, mUp_);
	return viewMatrix;
}

QMatrix4x4 Camera::getProjectionMatrix()
{
	return QMatrix4x4();
}

void Camera::setLastMousePos(QPoint pos)
{
	mLastPos_=pos;
}

void Camera::onRotate(QPoint pos)
{
	int dx=pos.x()-mLastPos_.x();
	int dy=pos.y()-mLastPos_.y();
	mLastPos_=pos;
	float delta_x=dx* sensitivity_;
	float delta_y=dy* sensitivity_;
	pitch(-delta_y);
	yaw(-delta_x);
}

void Camera::pitch(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, mRight_);
	mUp_ = rotateMat * mUp_;
	mPosition_ = rotateMat * mPosition_;

}

void Camera::yaw(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, mUp_);
	mUp_ = rotateMat * mUp_;
	mRight_ = rotateMat * mRight_;
	mPosition_ = rotateMat * mPosition_;
}
