#include "glwidget.h"
#include<iostream>
#include<QDebug>
#include<thread>
#include"camera/orthographicCamera.h"
#include"camera/perspectiveGameCamera.h"
#include"geometry.h"
GLWidget::GLWidget(QOpenGLWidget* parent)
	: QOpenGLWidget(parent)
{
	camera_ = std::make_shared<PerspectiveCamera>(65.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);
	//camera_=std::make_shared<OrthographicCamera>(-15.0f, 15.0f, -15.0f, 15.0f, -15.0f, 15.0f);
	//camera_ = std::make_shared<PerspectiveGameCamera>(65.0f, this->width() /this->height(), 0.1f, 1000.0f);
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
	glEnable(GL_CULL_FACE);									//开启面剔除
	glCullFace(GL_BACK);									//设置剔除背面
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	
	glClear(GL_COLOR_BUFFER_BIT);
	//geometry_ = Geometry::createSphere(4.5);

	std::shared_ptr<PhongMaterial> material = std::make_shared<PhongMaterial>();
	material->setTexture("resource/box.png");
	material->setSpecularTexture("resource/sp_mask.png");
	Mesh mesh(Geometry::createBox(4), material);
	meshs.push_back(mesh);


	render_ = std::make_shared<Renderer>();
	
	//geometry_=Geometry::createBox(3);
	//使用顶点缓冲区绘制
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//使用索引缓冲区绘制
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void GLWidget::paintGL()
{


	render_->render(meshs, camera_, std::make_shared<DirectionalLight>(),
		std::make_shared<AmbientLight>());

	/*
	* 绘制多个物体时需要分别绑定vao
	* 分别绑定texture
	* shder可以共用
	*/
	//QVector3D lightVec(-1, 0, -1);				//光照方向
	//QVector3D lightColor(1, 1, 1);

	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//清除颜色缓存和深度缓存
	//camera_->updataCameraPosition();
	//geometry_->getVAO()->bind();
	//geometry_->getShaderProgram()->bind();
	//geometry_->getTexture()->bind();

	//geometry_->getShaderProgram()->setUniformValue("transform", geometry_->getTransform());
	//geometry_->getShaderProgram()->setUniformValue("normalMatrix", geometry_->getNormalMatrix());
	//geometry_->getShaderProgram()->setUniformValue("viewMatrix", camera_->getViewMatrix());
	//geometry_->getShaderProgram()->setUniformValue("projectionMatrix", camera_->getProjectionMatrix());
	//geometry_->getShaderProgram()->setUniformValue("lightvec", lightVec);
	//geometry_->getShaderProgram()->setUniformValue("lightCol", lightColor);
	//geometry_->getShaderProgram()->setUniformValue("cameraPos", camera_->getCameraPosition());
	//geometry_->getShaderProgram()->setUniformValue("specularIntensity", specularIntensity);
	//geometry_->getShaderProgram()->setUniformValue("ambientColor", ambientColor);
	//geometry_->getShaderProgram()->setUniformValue("sampler", geometry_->getTexture()->textureId());
	//
	////glDrawArrays(GL_TRIANGLES,0,6);
	//glDrawElements(GL_TRIANGLES, geometry_->getNumVertices(), GL_UNSIGNED_INT, 0);
}

void GLWidget::resizeGL(int w, int h)
{
	camera_->setAspect(w, h);
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
	camera_->setLastMousePos(event->pos());
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton)
	{
		camera_->onRotate(event->pos());
		std::cout<<"camera position:"<<camera_->getCameraPosition().x()<<" "<<camera_->getCameraPosition().y()<<" "<<camera_->getCameraPosition().z()<<std::endl;
		
		update();
	}
	else if(event->buttons() & Qt::MiddleButton)
	{
		camera_->onMove(event->pos());
		update();
	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
	camera_->onMove(event->key(), true);
	update();
}

void GLWidget::keyReleaseEvent(QKeyEvent* event)
{
	camera_->onMove(event->key(), false);
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
	camera_->onZoom(event->delta());
	update();
}