#pragma once
#include<set>
#include"Camera.h"
#include"PerspectiveCamera.h"
class PerspectiveGameCamera :public PerspectiveCamera
{
public:
	PerspectiveGameCamera(float fov, float aspect, float Near, float Far);
	void onZoom(float delta);				//游戏视角，此实现为空
	void onMove(int key, bool is_press) override;					//游戏键盘移动
	void updataCameraPosition();
private:

	void pitch(float angle);
	void yaw(float angle);
	std::set<int> key_pressed_;
};