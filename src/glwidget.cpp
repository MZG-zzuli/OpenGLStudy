#include "../include/glwidget.h"
#include<iostream>
#include<QDebug>
#include"../include/OrthographicCamera.h"
#include"../include/perspectiveGameCamera.h"
#include"../include/geometry.h"
GLWidget::GLWidget(QOpenGLWidget* parent)
	: QOpenGLWidget(parent)
{
	//camera = std::make_shared<PerspectiveCamera>(65.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
	//camera=std::make_shared<OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	camera = std::make_shared<PerspectiveGameCamera>(65.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);
}
 
GLWidget::~GLWidget()
{
	 
}


void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);								//开启深度测试
	glDepthFunc(GL_LESS);									//设置深度测试方式为GL_LESS(近处遮挡远处)
	glClearDepthf(1.0);										//设置深度缓存的初始值为1.0f(默认值)
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	initShaders();
	initBuffers();
	initTexture();
	transform();
	
	glClear(GL_COLOR_BUFFER_BIT);
	//使用顶点缓冲区绘制
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//使用索引缓冲区绘制
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void GLWidget::paintGL()
{
	/*
	* 绘制多个物体时需要分别绑定vao
	* 分别绑定texture
	* shder可以共用
	*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存
	camera->updataCameraPosition();

	shader_program_->bind();
	vao_->bind();
	texture_->bind();
	shader_program_->setUniformValue("viewMatrix", camera->getViewMatrix());
	shader_program_->setUniformValue("projectionMatrix", camera->getProjectionMatrix());
	//glDrawArrays(GL_TRIANGLES,0,6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GLWidget::resizeGL(int w, int h)
{
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
	camera->setLastMousePos(event->pos());
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton)
	{
		camera->onRotate(event->pos());
		update();
	}
	else if(event->buttons() & Qt::MiddleButton)
	{
		camera->onMove(event->pos());
		update();
	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
	camera->onMove(event->key(), true);
}

void GLWidget::keyReleaseEvent(QKeyEvent* event)
{
	camera->onMove(event->key(), false);
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
	camera->onZoom(event->delta());
	update();
}

void GLWidget::initShaders()
{
	vertex_shader_ = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
	vertex_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/vertex.glsl");
	fragment_shader_ = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
	fragment_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/fragment.glsl");
	shader_program_ = std::make_shared<QOpenGLShaderProgram>();
	shader_program_->addShader(vertex_shader_.get());
	shader_program_->addShader(fragment_shader_.get());
	shader_program_->link();
	shader_program_->bind();
}

void GLWidget::initBuffers()
{
	vao_=std::make_shared<QOpenGLVertexArrayObject>();
	vao_->create();
	vao_->bind();
	vbo_ = std::make_shared<QOpenGLBuffer>();

	//顶点索引
	ebo_ = std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer);
	ebo_->create();
	ebo_->bind();
	unsigned int indices[] = {
		0, 1, 2,
		3,4,5
	};
	ebo_->allocate(indices, sizeof(indices));

	//顶点坐标
	float vertex_[] = {
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,
		0.5f,0.5f,0,
		0,0,0,
		0.5,0,0
	};
	vbo_->create();
	vbo_->bind();
	vbo_->allocate(vertex_, sizeof(vertex_));
	int aPos_location = shader_program_->attributeLocation("aPos");
	shader_program_->enableAttributeArray(aPos_location);
	//为其指定位置绑定对应的vbo(最近的vbo.bind())
	shader_program_->setAttributeBuffer(aPos_location, GL_FLOAT, 0, 3);
	//glVertexAttribPointer(aPos_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//颜色
	float colour[] = {
		1,0,0,
		0,1,0,
		0,0,1,
		0,0,0
	};
	color_vbo_ = std::make_shared<QOpenGLBuffer>();
	color_vbo_->create();
	color_vbo_->bind();
	color_vbo_->allocate(colour, sizeof(colour));
	int aCol_location = shader_program_->attributeLocation("aCol");
	shader_program_->enableAttributeArray(aCol_location);
	shader_program_->setAttributeBuffer(aCol_location, GL_FLOAT, 0, 3, 3 * sizeof(float));
}

void GLWidget::initTexture()
{
	//纹理坐标
	float uvs[]{
		0,0,
		1,0,
		0,1,
		1,0,
		0,1,
		1,1
	};
	uv_vbo_ = std::make_shared<QOpenGLBuffer>();
	uv_vbo_->create();
	uv_vbo_->bind();
	uv_vbo_->allocate(uvs, sizeof(uvs));
	int aUV_location = shader_program_->attributeLocation("uv");
	shader_program_->enableAttributeArray(aUV_location);
	shader_program_->setAttributeBuffer(aUV_location, GL_FLOAT, 0, 2, 2 * sizeof(float));

	//纹理
	texture_ = std::make_shared<QOpenGLTexture>(QImage("E:/QtProject/GLStudy/resource/goku.jpg").mirrored());
	texture_->setMinificationFilter(QOpenGLTexture::Nearest);
	texture_->setMagnificationFilter(QOpenGLTexture::Linear);
	int texture_id = texture_->textureId();
	texture_->bind(texture_id);
	shader_program_->setUniformValue("sampler", texture_id);
}

void GLWidget::transform()
{
	//所有变换都是在原有的基础上进行的
	//y轴旋转矩阵
	//transMatrix.rotate(angle, QVector3D(0.0f, 1.0f, 0.0f));
	//shader_program_->setUniformValue("transMatrix", transMatrix);

	//看的位置，方向，相机顶部方向
	viewMatrix.lookAt(QVector3D(-0.5f, 0.0f, 0.5f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
	shader_program_->setUniformValue("viewMatrix", camera->getViewMatrix());

	//perspectMatrix.perspective(glm::radians(65.0f), 1920.0f / 1080.0f, 0.5f, 100.0f);
	//相机视张角度，宽高比，近裁剪面，远裁剪面
	//perspectMatrix.perspective(65.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
	shader_program_->setUniformValue("perspectiveMatrix", camera->getProjectionMatrix());
}

