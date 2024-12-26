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
#include"PerspectiveCamera.h"
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
    void initShaders();
    void initBuffers();
    void initTexture();
    void transform();
    std::shared_ptr<QOpenGLShader> vertex_shader_ = nullptr;
    std::shared_ptr<QOpenGLShader> fragment_shader_ = nullptr;
    std::shared_ptr< QOpenGLShaderProgram> shader_program_ = nullptr;
    std::shared_ptr<QOpenGLVertexArrayObject> vao_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> vbo_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> color_vbo_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> uv_vbo_ = nullptr;
    std::shared_ptr<QOpenGLTexture> texture_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> ebo_ = nullptr;
    QMatrix4x4 viewMatrix=QMatrix4x4();
    //QMatrix4x4 perspectMatrix=QMatrix4x4();
    std::shared_ptr<Camera> camera=nullptr;
    float angle=0.0f;
    QMatrix4x4 transMatrix=QMatrix4x4();
    QPoint lastPos;
};
#endif // GLWIDGET_H
