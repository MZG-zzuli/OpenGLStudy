#include "glwidget.h"
#include<glm/glm.hpp>
#include<iostream>
GLWidget::GLWidget(QOpenGLWidget *parent)
    : QOpenGLWidget(parent)
{
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    vertex_shader_=new QOpenGLShader(QOpenGLShader::Vertex);
    vertex_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/vertex.glsl");
    fragment_shader_=new QOpenGLShader(QOpenGLShader::Fragment);
    fragment_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/fragment.glsl");
    shader_program_=new QOpenGLShaderProgram;
    shader_program_->addShader(vertex_shader_);
    shader_program_->addShader(fragment_shader_);
    shader_program_->link();
    shader_program_->bind();
    vbo_=new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    float _vertex[] = {
     0.0,  0.5, 0.0,
    -0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
    };
    vbo_->create();
    vbo_->bind();
    vbo_->allocate(_vertex, sizeof(_vertex));
    shader_program_->enableAttributeArray(0);
    int a_Pos_location=shader_program_->attributeLocation("aPos");
    shader_program_->setAttributeBuffer(a_Pos_location, GL_FLOAT, 0, 3, 3 * sizeof(float));
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);



    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    shader_program_->bind();
    glDrawArrays(GL_TRIANGLES,0,3);
    std::cout<<"paintGL"<<std::endl;
}

void GLWidget::resizeGL(int w, int h)
{
}

