#pragma once

#include<memory>
#include<vector>
#include"mesh.h"
#include"light/light.h"
#include"light/directionalLight.h"
#include"light/ambientLight.h"
#include"light/pointLight.h"
#include"camera/camera.h"
#include"material/material.h"
#include"material/phongMaterial.h"
#include"material/whiteMaterial.h"
#include<QOpenGLExtraFunctions>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
class Renderer:public QOpenGLExtraFunctions
{
public:
	Renderer();
	~Renderer();
	void render(std::vector<Mesh>& meshs,std::shared_ptr<Camera> camera_,
		std::shared_ptr<PointLight> directional_light,std::shared_ptr<AmbientLight> ambient_light);
	
private:
	void phongRender(Mesh& mesh, std::shared_ptr<Camera> camera, std::shared_ptr<PointLight> light,
		std::shared_ptr<AmbientLight> ambient_light, std::shared_ptr<QOpenGLShaderProgram> shader);
	void whiteRender(Mesh& mesh, std::shared_ptr<Camera> camera, std::shared_ptr<QOpenGLShaderProgram> shader);



};