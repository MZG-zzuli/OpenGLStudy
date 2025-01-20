#pragma once
#include<QOpenGLTexture>
#include<memory>
#include<mutex>
#include"material/material.h"
class PhongMaterial:public Material
{
public:
	static std::shared_ptr<QOpenGLShaderProgram> getShaderProgram();
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
	static std::once_flag shader_program_flag_;
};