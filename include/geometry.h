#pragma once
#include<QOpenGLWidget>
#include<QOpenGLVertexArrayObject>
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLShader>
#include<QOpenGLTexture>
#include<QtMath>
#include<memory>
#include<vector>
#include<QMatrix4x4>
#include<QMatrix3x3>
class Geometry
{
public:
    Geometry();
    ~Geometry();
    std::shared_ptr<QOpenGLShaderProgram> getShaderProgram();
    std::shared_ptr<QOpenGLVertexArrayObject> getVAO();
    std::shared_ptr<QOpenGLTexture> getTexture();
    QMatrix4x4 getTransform();
    //获取法线矩阵(法线随着模型坐标变化而变化)
    QMatrix3x3 getNormalMatrix() const;
    GLuint getNumVertices() const;
    static std::shared_ptr<Geometry> createBox(float size);     //边长
    static std::shared_ptr<Geometry> createSphere(float size);  ///半径

private:
    QMatrix4x4 transform_=QMatrix4x4();
    std::shared_ptr<QOpenGLTexture> texture_ = nullptr;
    std::shared_ptr<QOpenGLShaderProgram> shader_program_ = nullptr;
    std::shared_ptr<QOpenGLVertexArrayObject> vao_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> pos_vbo_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> nor_vbo_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> col_vbo_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> uv_vbo_ = nullptr;
    std::shared_ptr<QOpenGLBuffer> ebo_ = nullptr;
    GLuint num_vertices_ = 0;
};