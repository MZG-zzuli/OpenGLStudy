#include "camera/orthographicCamera.h"


OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float Near, float Far):
	left_(left),
	right_(right),
	bottom_(bottom),
	top_(top),
	near_(Near),
	far_(Far)
{
}

QMatrix4x4 OrthographicCamera::getProjectionMatrix()
{
	QMatrix4x4 projectionMatrix;
	//根据窗口的宽高和视口的宽高计算出正确的视口
	//如果窗口的宽高比大于视口的宽高比，则视口的宽度需要增大，以适应窗口的宽高比
	//如果窗口的宽高比小于视口的宽高比，则视口的高度需要增大，以适应窗口的宽高比
	float window_aspect = width_ /(float) height_;
	float viewport_aspect = (right_ - left_) / (top_ - bottom_);
	float left=left_, right=right_, bottom=bottom_, top=top_;
	if (window_aspect > viewport_aspect)
	{
		left=left_ * window_aspect;
		right=right_ * window_aspect;
	}
	else
	{
		top=top_/window_aspect;
		bottom=bottom_/window_aspect;
	}
	float zoom=std::pow(2.0f, zoom_);
	projectionMatrix.ortho(left * zoom, right * zoom, bottom * zoom, top * zoom, near_, far_);
	return projectionMatrix;
}

void OrthographicCamera::onZoom(float delta)
{
	zoom_ -= delta * zoom_speed_;
}

void OrthographicCamera::setAspect(int width, int height)
{
	width_ = width;
	height_ = height;
}
