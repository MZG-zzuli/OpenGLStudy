#include"PerspectiveCamera.h"



PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float Near, float Far):
	m_fov_(fov),
	m_aspect_(aspect),
	m_near_(Near),
	m_far_(Far)
{
}

QMatrix4x4 PerspectiveCamera::getProjectionMatrix()
{
	QMatrix4x4 projectionMatrix;
	projectionMatrix.perspective(m_fov_, m_aspect_, m_near_, m_far_);
	return projectionMatrix;
}
