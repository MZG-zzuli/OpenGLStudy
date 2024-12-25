#include "OrthographicCamera.h"


OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float Near, float Far):
	m_left_(left),
	m_right_(right),
	m_bottom_(bottom),
	m_top_(top),
	near_(Near),
	far_(Far)
{
}

QMatrix4x4 OrthographicCamera::getProjectionMatrix()
{
	QMatrix4x4 projectionMatrix;
	float zoom=std::pow(2.0f, zoom_);
	projectionMatrix.ortho(m_left_ * zoom, m_right_ * zoom, m_bottom_ * zoom, m_top_ * zoom, near_, far_);
	return projectionMatrix;
}

void OrthographicCamera::onZoom(float delta)
{
	zoom_ += delta * zoom_speed_;
}
