#pragma once

#include<QVector3D>
#include<QOpenGLWidget>
class Light
{
public:
    Light();
    virtual ~Light();
    QVector3D getColor() const;
    void setColor(const QVector3D& color);
    GLfloat getSpecularIntensity() const;				//获取镜面反射强度
    void setSpecularIntensity(GLfloat intensity);		//设置镜面反射强度
protected:
    QVector3D color_{ 1.0f, 1.0f, 1.0f };
    GLfloat specular_intensity_{ 0.8f };				//镜面反射强度


};