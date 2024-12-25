#pragma once
#include "Camera.h"
class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float Near, float Far);
	QMatrix4x4 getProjectionMatrix() override;
	void onZoom(float delta) override;
private:
	float zoom_ = 0.0f;				//缩放系数
	float zoom_speed_ = 0.003;		//缩放速度
	float m_left_, m_right_, m_bottom_, m_top_, near_, far_;

};