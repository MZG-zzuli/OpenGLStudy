#include "renderer/renderer.h"



Renderer::Renderer()
{
	initializeOpenGLFunctions();
}

Renderer::~Renderer()
{
}

void Renderer::render(std::vector<Mesh>& meshs, std::shared_ptr<Camera> camera_, 
	std::shared_ptr<PointLight> directional_light, std::shared_ptr<AmbientLight> ambient_light)
{
	camera_->updataCameraPosition();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < meshs.size(); i++)
	{
		Mesh& mesh=meshs[i];
		if (mesh.getMaterial()->getMaterialType() == MaterialType::PhongMaterial)
		{
			phongRender(mesh, camera_, directional_light, ambient_light, PhongMaterial::getShaderProgram());
		}
		else if (mesh.getMaterial()->getMaterialType() == MaterialType::WhiteMaterial)
		{
			whiteRender(mesh, camera_, WhiteMaterial::getShaderProgram());
		}
		glDrawElements(GL_TRIANGLES, mesh.getGeometry()->getNumVertices(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::phongRender(Mesh& mesh, std::shared_ptr<Camera> camera,
	std::shared_ptr<PointLight> light, std::shared_ptr<AmbientLight> ambient_light, 
	std::shared_ptr<QOpenGLShaderProgram> shader)
{
	shader->bind();
	std::shared_ptr<Geometry> geometry = mesh.getGeometry();
	std::shared_ptr<PhongMaterial> material = std::dynamic_pointer_cast<PhongMaterial>(mesh.getMaterial());
	if (material == nullptr)
	{
		return;
	}
	geometry->getVAO()->bind();
	material->getTexture()->bind();
	GLuint textid=material->getTexture()->textureId();
	material->getTexture()->bind(textid);
	GLuint specular_map_id=material->getSpecularTexture()->textureId();
	material->getSpecularTexture()->bind(specular_map_id);

	shader->setUniformValue("sampler", material->getTexture()->textureId());
	shader->setUniformValue("specular_map", material->getSpecularTexture()->textureId());
	shader->setUniformValue("modelMatrix", mesh.getModelMatrix());
	shader->setUniformValue("normalMatrix", mesh.getNormalMatrix());	//todo normalMatrix计算没有考虑modeMatrix
	shader->setUniformValue("viewMatrix", camera->getViewMatrix());
	shader->setUniformValue("projectionMatrix", camera->getProjectionMatrix());
	shader->setUniformValue("lightPosition", light->getPosition());
	shader->setUniformValue("lightCol", light->getColor());
	shader->setUniformValue("cameraPos", camera->getCameraPosition());
	shader->setUniformValue("specularIntensity", light->getSpecularIntensity());
	shader->setUniformValue("ambientColor", ambient_light->getColor());
	shader->setUniformValue("k1", light->getAttenuationK1());
	shader->setUniformValue("k2", light->getAttenuationK2());
	shader->setUniformValue("kc", light->getAttenuationKc());
}

void Renderer::whiteRender(Mesh& mesh, std::shared_ptr<Camera> camera, std::shared_ptr<QOpenGLShaderProgram> shader)
{
	shader->bind();
	std::shared_ptr<Geometry> geometry = mesh.getGeometry();
	geometry->getVAO()->bind();
	shader->setUniformValue("modelMatrix", mesh.getModelMatrix());
	shader->setUniformValue("viewMatrix", camera->getViewMatrix());
	shader->setUniformValue("projectionMatrix", camera->getProjectionMatrix());

}
