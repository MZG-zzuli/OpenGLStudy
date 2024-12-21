#pragma once
#include<QOpenGLWidget>
#include<QVector3D>
#include<QMatrix4x4>
class Camera
{
public:
    Camera();
    virtual ~Camera();
    virtual QMatrix4x4 getViewMatrix();
    virtual QMatrix4x4 getProjectionMatrix();
    void setLastMousePos(QPoint pos);               //当鼠标按下时记录鼠标位置
    virtual void onRotate(QPoint pos);
private:
    virtual void pitch(float angle);                //俯仰角(上下旋转)
    virtual void yaw(float angle);                  //偏航角(左右旋转)
    float sensitivity_ = 0.5f;                     //鼠标灵敏度
    QPoint mLastPos_ = QPoint(0, 0);                //鼠标上一次位置
    QVector3D mPosition_ = QVector3D(0, 0, 1.0);   //相机位置
    QVector3D mUp_ = QVector3D(0, 1, 0);            //相机上方向
    QVector3D mRight_ = QVector3D(1, 0, 0);         //相机右方向

};