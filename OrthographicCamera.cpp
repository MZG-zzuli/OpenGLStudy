#include "OrthographicCamera.h"


OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float Near, float Far):
	m_left_(left),
	m_right_(right),
	m_bottom_(bottom),
	m_top_(top),
	m_near_(Near),
	m_far_(Far)
{
}

QMatrix4x4 OrthographicCamera::getProjectionMatrix()
{
	QMatrix4x4 projectionMatrix;
	projectionMatrix.ortho(m_left_, m_right_, m_bottom_, m_top_, m_near_, m_far_);
	return projectionMatrix;
}