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
    QOpenGLBuffer* ebo_;
};
#endif // GLWIDGET_H
