#pragma once
#include<QOpenGLWidget>
#include<QVector3D>
#include<QMatrix4x4>
class Object
{
public:
    Object();
    virtual ~Object();
    void setPosition(QVector3D position);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void setScale(QVector3D scale);
    QMatrix4x4 getModelMatrix();
protected:
    QVector3D position_{0,0,0};
    float angle_x_{ 0 };
    float angle_y_{ 0 };
    float angle_z_{ 0 };
    QVector3D scale_{ 1,1,1 };


};
