#pragma once

#include<memory>
#include<vector>
#include"mesh.h"
#include"light/light.h"
#include"light/directionalLight.h"
#include"light/ambientLight.h"
#include"light/pointLight.h"
#include"light/spotLight.h"
#include"camera/camera.h"
#include"material/material.h"
#include"material/phongMaterial.h"
#include"material/whiteMaterial.h"
#include"material/depthMaterial.h"
#include<QOpenGLExtraFunctions>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
#include"scene.h"
class Renderer:public QOpenGLExtraFunctions
{
public:
	Renderer();
	~Renderer();
	void render(std::shared_ptr<Scene> mesh, std::shared_ptr<Camera> camera_,
		std::shared_ptr<SpotLight> spot_light, std::vector<DirectionalLight> directional_lights,
		std::shared_ptr<AmbientLight> ambient_light);
	void renderObject(std::shared_ptr<Object> object,std::shared_ptr<Camera> camera_,
		std::shared_ptr<SpotLight> spot_light, std::vector<DirectionalLight> directional_lights,
		std::shared_ptr<AmbientLight> ambient_light);
	
private:
	//设置渲染状态
	void setRenderState(std::shared_ptr<Material> material);
	void phongRender(std::shared_ptr<Mesh> mesh, std::shared_ptr<Camera> camera, std::shared_ptr<SpotLight> spot_light,
		std::vector<DirectionalLight> directional_lights,std::shared_ptr<AmbientLight> ambient_light,
		std::shared_ptr<QOpenGLShaderProgram> shader);
	void whiteRender(std::shared_ptr<Mesh> mesh, std::shared_ptr<Camera> camera, std::shared_ptr<QOpenGLShaderProgram> shader);
	void depthRender(std::shared_ptr<Mesh> mesh, std::shared_ptr<Camera> camera, std::shared_ptr<QOpenGLShaderProgram> shader);


};