#pragma once
#include<QOpenGLWidget>
#include<QVector3D>
#include<QMatrix4x4>
class Camera
{
public:
    Camera();
    virtual ~Camera();
    virtual QMatrix4x4 getViewMatrix();             //在哪里看
    virtual QMatrix4x4 getProjectionMatrix() = 0;   //投影方式(子类实现，正交和透视)
    void setLastMousePos(QPoint pos);               //当鼠标按下时记录鼠标位置
    QVector3D getCameraPosition() const;            //获取相机位置
    virtual void onRotate(QPoint pos);
    virtual void onMove(QPoint pos);
    virtual void onZoom(float delta) = 0;
    virtual void onMove(int key,bool is_press);
    virtual void updataCameraPosition();
    virtual void setAspect(float aspect);
protected:
    QVector3D camera_up_ = QVector3D(0, 1, 0);            //相机上方向
    QVector3D camera_right_ = QVector3D(1, 0, 0);         //相机右方向
    QVector3D camera_position_ = QVector3D(0, 0, 5.0);    //相机位置
private:
    virtual void pitch(float angle);                //俯仰角(上下旋转)
    virtual void yaw(float angle);                  //偏航角(左右旋转)
    float sensitivity_ = 0.5f;                      //物体转动灵敏度
    float move_speed_ = 0.005f;                     //物体移动速度
    QPoint last_pos_ = QPoint(0, 0);                //鼠标上一次位置

};