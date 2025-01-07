#pragma once

#include<memory>
#include<vector>
#include"mesh.h"
#include"light/light.h"
#include"light/directionalLight.h"
#include"light/ambientLight.h"
#include"camera/camera.h"
#include"material/material.h"
#include"material/phongMaterial.h"
#include<QOpenGLExtraFunctions>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
class Renderer:public QOpenGLExtraFunctions
{
public:
	Renderer();
	~Renderer();
	void render(std::vector<Mesh>& meshs,std::shared_ptr<Camera> camera_,
		std::shared_ptr<DirectionalLight> directional_light,std::shared_ptr<AmbientLight> ambient_light);
	void phongRender(Mesh& mesh, std::shared_ptr<Camera> camera_, std::shared_ptr<DirectionalLight> directional_light,
		std::shared_ptr<AmbientLight> ambient_light, std::shared_ptr<QOpenGLShaderProgram> shader);
private:
	//根据指定的shader code文件路径创建shader
	std::shared_ptr<QOpenGLShaderProgram> createShader(QString vertex_shader_file, QString fragment_shader_file);
	//根据指定的材质类型获取对应的shader
	std::shared_ptr<QOpenGLShaderProgram> pickShader(MaterialType type);
	std::shared_ptr<QOpenGLShaderProgram> phone_shader_=nullptr;



};