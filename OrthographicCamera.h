#pragma once
#include "Camera.h"
class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float Near, float Far);
	QMatrix4x4 getProjectionMatrix() override;
private:
	float m_left_, m_right_, m_bottom_, m_top_, m_near_, m_far_;

};