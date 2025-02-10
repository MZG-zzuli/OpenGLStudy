#pragma once
#include<QOpenGLWidget>
#include<QVector3D>
#include<QMatrix4x4>
#include<set>
#include<memory>
enum class ObjectType
{
    Object,
    Mesh,
    Scene
};

class Object:public std::enable_shared_from_this<Object>
{
public:
    Object();
    virtual ~Object();
    ObjectType getObjectType() const;
    void setPosition(QVector3D position);   //设置位置
    QVector3D getPosition() const;          //返回位置
    void setAngle(QVector3D angle);         //设置角度
    void setAngleX(GLfloat angle);
    GLfloat getAngleX() const;
    void setAngleY(GLfloat angle);
    GLfloat getAngleY() const;
    void setAngleZ(GLfloat angle);
    GLfloat getAngleZ() const;
    void setScale(QVector3D scale);         //设置缩放
    QVector3D getScale() const;
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    QMatrix4x4 getModelMatrix();
    QMatrix3x3 getNormalMatrix();
    std::shared_ptr<Object> getParent() const;
    std::set<std::shared_ptr<Object>>& getChildrens();
    void addChild(std::shared_ptr<Object> child);
protected:
    QVector3D position_{0,0,0};
    float angle_x_{ 0 };
    float angle_y_{ 0 };
    float angle_z_{ 0 };
    QVector3D scale_{ 1,1,1 };
    ObjectType type_;
private:
    void setParent(std::shared_ptr<Object> parent);
    std::weak_ptr<Object> parent_;
    std::set<std::shared_ptr<Object>> childrens_;

};
