#include "../include/Camera.h"
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

void Camera::setLastMousePos(QPoint pos)
{
	last_pos_=pos;
}

void Camera::onRotate(QPoint pos)
{
	int dx=pos.x()-last_pos_.x();
	int dy=pos.y()-last_pos_.y();
	last_pos_=pos;
	float delta_x=dx* sensitivity_;
	float delta_y=dy* sensitivity_;
	pitch(-delta_y);
	yaw(-delta_x);
}

void Camera::onMove(QPoint pos)
{
	int dx = pos.x() - last_pos_.x();
	int dy = pos.y() - last_pos_.y();
	last_pos_ = pos;
	mPosition_ -= mRight_ * dx * move_speed_;
	mPosition_ += mUp_ * dy * move_speed_;
}

void Camera::onMove(int key,bool is_press)
{
}

void Camera::updataCameraPosition()
{
}

void Camera::pitch(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, mRight_);				//绕右向量(相机x轴)旋转
	mUp_ = rotateMat * mUp_;
	mPosition_ = rotateMat * mPosition_;

}

void Camera::yaw(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, QVector3D(0, 1, 0));	//绕世界y轴旋转
	mUp_ = rotateMat * mUp_;
	mRight_ = rotateMat * mRight_;
	mPosition_ = rotateMat * mPosition_;
}
