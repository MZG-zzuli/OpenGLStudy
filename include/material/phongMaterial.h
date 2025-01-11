#pragma once
#include<QOpenGLTexture>
#include<memory>
#include"material.h"
class PhongMaterial:public Material
{
public:
	PhongMaterial();
	~PhongMaterial();
	void setTexture(std::shared_ptr<QOpenGLTexture> texture);
	void setShiness(GLfloat shiness);
	void setTexture(QString texture_path);
	std::shared_ptr<QOpenGLTexture> getTexture() const;
	void setSpecularTexture(std::shared_ptr<QOpenGLTexture> texture);
	void setSpecularTexture(QString texture_path);
	std::shared_ptr<QOpenGLTexture> getSpecularTexture() const;
private:
	std::shared_ptr<QOpenGLTexture> texture_=nullptr;
	std::shared_ptr<QOpenGLTexture> specular_texture_=nullptr;
	GLfloat shiness_{ 1.0f };

};