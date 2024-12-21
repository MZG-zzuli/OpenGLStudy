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
    QOpenGLShader* vertex_shader_;
    QOpenGLShader* fragment_shader_;
    QOpenGLShaderProgram* shader_program_;
    QOpenGLVertexArrayObject* vao_;
    QOpenGLBuffer* vbo_;
    QOpenGLBuffer* color_vbo_;
    QOpenGLBuffer* uv_vbo_;
    QOpenGLTexture* texture_;
    QOpenGLBuffer* ebo_;
    QMatrix4x4 viewMatrix=QMatrix4x4();
    QMatrix4x4 perspectMatrix=QMatrix4x4();
};
#endif // GLWIDGET_H
