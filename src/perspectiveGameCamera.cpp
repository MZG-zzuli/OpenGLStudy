#include"../include/perspectiveGameCamera.h"

PerspectiveGameCamera::PerspectiveGameCamera(float fov, float aspect, float Near, float Far):
	PerspectiveCamera(fov, aspect, Near, Far)
{

}



void PerspectiveGameCamera::onZoom(float delta)
{
}

void PerspectiveGameCamera::onMove(int key, bool is_press)
{
	if (is_press)
	{
		key_pressed_.insert(key);
	}
	else
	{
		key_pressed_.erase(key);
	}
}

void PerspectiveGameCamera::updataCameraPosition()
{
	QVector3D front = QVector3D::crossProduct(camera_up_, camera_right_);
	QVector3D moveVec(0, 0, 0);
	if (key_pressed_.count(Qt::Key_W))
	{
		moveVec += front;
	}
	if (key_pressed_.count(Qt::Key_A))
	{
		moveVec -= camera_right_;
	}
	if (key_pressed_.count(Qt::Key_S))
	{
		moveVec -= front;
	}
	if (key_pressed_.count(Qt::Key_D))
	{
		moveVec += camera_right_;
	}
	moveVec.normalize();
	camera_position_ += moveVec;
}

void PerspectiveGameCamera::pitch(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, camera_right_);				//绕右向量(相机x轴)旋转
	camera_up_ = rotateMat * camera_up_;
}

void PerspectiveGameCamera::yaw(float angle)
{
	QMatrix4x4 rotateMat;
	rotateMat.rotate(angle, QVector3D(0, 1, 0));	//绕世界y轴旋转
	camera_up_ = rotateMat * camera_up_;
	camera_right_ = rotateMat * camera_right_;
}


