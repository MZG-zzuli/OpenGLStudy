#include"camera/perspectiveCamera.h"



PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float Near, float Far):
	fov_(fov),
	aspect_(aspect),
	near_(Near),
	far_(Far)
{
}

QMatrix4x4 PerspectiveCamera::getProjectionMatrix()
{
	QMatrix4x4 projectionMatrix;
	projectionMatrix.perspective(fov_, aspect_, near_, far_);
	return projectionMatrix;
}

void PerspectiveCamera::onZoom(float delta)
{
	QVector3D front= QVector3D::crossProduct(camera_up_, camera_right_);
	camera_position_ += front * delta * zoom_speed_;
}

void PerspectiveCamera::setAspect(int width, int height)
{
	aspect_ = width / (float)height;
}
