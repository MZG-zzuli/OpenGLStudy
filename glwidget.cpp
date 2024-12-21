#include "glwidget.h"
#include<glm/glm.hpp>
#include<iostream>
GLWidget::GLWidget(QOpenGLWidget* parent)
	: QOpenGLWidget(parent)
{
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	vertex_shader_ = new QOpenGLShader(QOpenGLShader::Vertex);
	vertex_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/vertex.glsl");
	fragment_shader_ = new QOpenGLShader(QOpenGLShader::Fragment);
	fragment_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/fragment.glsl");
	shader_program_ = new QOpenGLShaderProgram;
	shader_program_->addShader(vertex_shader_);
	shader_program_->addShader(fragment_shader_);
	shader_program_->link();
	shader_program_->bind();
	vbo_ = new QOpenGLBuffer();

	//顶点索引
	ebo_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	ebo_->create();
	ebo_->bind();
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	ebo_->allocate(indices, sizeof(indices));

	//顶点坐标
	float vertex_[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f
	};
	vbo_->create();
	vbo_->bind();
	vbo_->allocate(vertex_, sizeof(vertex_));
	int aPos_location = shader_program_->attributeLocation("aPos");
	shader_program_->enableAttributeArray(aPos_location);
	//为其指定位置绑定对应的vbo(最近的vbo.bind())
	shader_program_->setAttributeBuffer(aPos_location, GL_FLOAT, 0, 3, 3 * sizeof(float));
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//颜色
	float colour[] = {
		1,0,0,
		0,1,0,
		0,0,1,
		0,0,0
	};
	color_vbo_ = new QOpenGLBuffer();
	color_vbo_->create();
	color_vbo_->bind();
	color_vbo_->allocate(colour, sizeof(colour));
	int aCol_location = shader_program_->attributeLocation("aCol");
	shader_program_->enableAttributeArray(aCol_location);
	shader_program_->setAttributeBuffer(aCol_location, GL_FLOAT, 0, 3, 3 * sizeof(float));

	//纹理坐标
	float uvs[]{
		0,0,
		1,0,
		0,1,
		1,1
	};
	uv_vbo_ = new QOpenGLBuffer();
	uv_vbo_->create();
	uv_vbo_->bind();
	uv_vbo_->allocate(uvs, sizeof(uvs));
	int aUV_location = shader_program_->attributeLocation("uv");
	shader_program_->enableAttributeArray(aUV_location);
	shader_program_->setAttributeBuffer(aUV_location, GL_FLOAT, 0, 2, 2 * sizeof(float));

	//纹理
	texture_ = new QOpenGLTexture(QImage("E:/QtProject/GLStudy/resource/1.jpg").mirrored());
	texture_->setMinificationFilter(QOpenGLTexture::Nearest);
	texture_->setMagnificationFilter(QOpenGLTexture::Linear);
	int texture_id = texture_->textureId();
	texture_->bind(texture_id);
	shader_program_->setUniformValue("sampler", texture_id);
	auto mat=viewMatrix;

	//看的位置，方向，相机顶部方向
	viewMatrix.lookAt(QVector3D(-0.5f, 0.0f, 0.5f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
	shader_program_->setUniformValue("viewMatrix", viewMatrix);

	//perspectMatrix.perspective(glm::radians(65.0f), 1920.0f / 1080.0f, 0.5f, 100.0f);
	//相机视张角度，宽高比，近裁剪面，远裁剪面
	perspectMatrix.perspective(65.0f, 1920.0f / 1080.0f, 0.5f, 100.0f);
	shader_program_->setUniformValue("perspectiveMatrix", perspectMatrix);


	glClear(GL_COLOR_BUFFER_BIT);
	//使用顶点缓冲区绘制
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//使用索引缓冲区绘制
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	shader_program_->bind();
	texture_->bind(); 
	shader_program_->setUniformValue("viewMatrix", viewMatrix);
	shader_program_->setUniformValue("perspectMatrix", perspectMatrix);

	//glDrawArrays(GL_TRIANGLES,0,3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GLWidget::resizeGL(int w, int h)
{
}

