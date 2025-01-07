#pragma once

#include<QVector3D>
#include<QOpenGLWidget>
class Light
{
public:
    Light();
    virtual ~Light();
    QVector3D getColor() const;

protected:
    QVector3D color_{ 1.0f, 1.0f, 1.0f };


};