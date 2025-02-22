#include "camera/camera.h"


Camera::Camera(float Near, float Far):near_(Near), far_(Far)
{
}

Camera::~Camera()
{
}

QMatrix4x4 Camera::getViewMatrix()
{
	QVector3D front = QVector3D::crossProduct(camera_up_, camera_right_);
	QVector3D center= camera_position_ + front;
	QMatrix4x4 viewMatrix;
	viewMatrix.lookAt(camera_position_, center, camera_up_);
	return viewMatrix;
}

void Camera::setLastMousePos(QPoint pos)
{
	last_pos_=pos;
}

QVector3D Camera::getCameraPosition() const
{
	return camera_position_;
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
	camera_position_ -= camera_right_ * dx * move_speed_;
	camera_position_ += camera_up_ * dy * move_speed_;
}

void Camera::onMove(int key,bool is_press)
{
}

void Camera::updataCameraPosition()
{
}

void Camera::setAspect(int width, int height)
{
}

float Camera::getNear() const
{
	return near_;
}

float Camera::getFar() const
{
	return far_;
}

void Camera::pitch(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, camera_right_);				//绕右向量(相机x轴)旋转
	camera_up_ = rotateMat * camera_up_;
	camera_position_ = rotateMat * camera_position_;

}

void Camera::yaw(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, QVector3D(0, 1, 0));	//绕世界y轴旋转
	camera_up_ = rotateMat * camera_up_;
	camera_right_ = rotateMat * camera_right_;
	camera_position_ = rotateMat * camera_position_;
}
