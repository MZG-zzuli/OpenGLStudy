#pragma once
#include"Camera.h"
//透视投影
class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float aspect, float Near, float Far);
	QMatrix4x4 getProjectionMatrix() override;
private:
	float m_fov_;		//视角,角度
	float m_aspect_;	//纵横(宽高)比 
	float m_near_;		//近裁剪面
	float m_far_;		//远裁剪面


};