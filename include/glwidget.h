#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QOpenGLExtraFunctions>
#include<QOpenGLVertexArrayObject>
#include<QOpenGLBuffer>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include<QtMath>
#include<QMouseEvent>
#include<memory>
#include"renderer/renderer.h"
#include"camera/perspectiveCamera.h"
#include"geometry.h"
#include"light/pointLight.h"
#include"light/spotLight.h"
class WhiteMaterial;
#include"material/whiteMaterial.h"
class GLWidget : public QOpenGLWidget,public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    
    GLWidget(QOpenGLWidget *parent = nullptr);
    ~GLWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w,int h) override;

private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;          //wasd控制摄像机移动
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    std::shared_ptr<Geometry> geometry_ = nullptr;
    std::vector<Mesh> meshs;
    std::shared_ptr<Renderer> render_ = nullptr;
    std::shared_ptr<Camera> camera_=nullptr;
    float specularIntensity = 0.5f;                     //高光强度
    QVector3D ambientColor{ 0.2f, 0.2f, 0.2f };         //环境光
    std::shared_ptr<SpotLight> spot_light_ = nullptr;
    std::vector<DirectionalLight> directional_lights_;
    float t = 0;
};
#endif // GLWIDGET_H
