#pragma once
#include"Camera.h"
//透视投影
class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float aspect, float Near, float Far);
	QMatrix4x4 getProjectionMatrix() override;
	void onZoom(float delta) override;
	void setAspect(int width, int height);
private:
	float zoom_speed_ =0.003;		//缩放速度
	float fov_;						//视角,角度
	float aspect_;					//纵横(宽高)比 


};