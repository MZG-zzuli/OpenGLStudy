#include "renderer/renderer.h"



Renderer::Renderer()
{
	initializeOpenGLFunctions();
}

Renderer::~Renderer()
{
}

void Renderer::render(std::shared_ptr<Scene> mesh, std::shared_ptr<Camera> camera_, std::shared_ptr<SpotLight> spot_light, std::vector<DirectionalLight> directional_lights, std::shared_ptr<AmbientLight> ambient_light)
{
	camera_->updataCameraPosition();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderObject(mesh, camera_, spot_light, directional_lights, ambient_light);
}

void Renderer::renderObject(std::shared_ptr<Object> object, std::shared_ptr<Camera> camera_,
	std::shared_ptr<SpotLight> spot_light, std::vector<DirectionalLight> directional_lights,
	std::shared_ptr<AmbientLight> ambient_light)
{

	if (object->getObjectType() == ObjectType::Mesh)	//如果是mesh，则渲染
	{
		std::shared_ptr<Mesh> mesh=std::dynamic_pointer_cast<Mesh>(object);
		if (mesh->getMaterial()->getMaterialType() == MaterialType::PhongMaterial)
		{
			phongRender(mesh, camera_, spot_light, directional_lights, ambient_light, PhongMaterial::getShaderProgram());
		}
		else if (mesh->getMaterial()->getMaterialType() == MaterialType::WhiteMaterial)
		{
			whiteRender(mesh, camera_, WhiteMaterial::getShaderProgram());
		}
		glDrawElements(GL_TRIANGLES, mesh->getGeometry()->getNumVertices(), GL_UNSIGNED_INT, 0);
	}
	std::set<std::shared_ptr<Object>>& objects = object->getChildrens();
	for (auto object_child : objects)
	{
		renderObject(object_child, camera_, spot_light, directional_lights, ambient_light);
	}

}

void Renderer::phongRender(std::shared_ptr<Mesh> mesh, std::shared_ptr<Camera> camera,
	std::shared_ptr<SpotLight> spot_light, std::vector<DirectionalLight> directional_lights, std::shared_ptr<AmbientLight> ambient_light,
	std::shared_ptr<QOpenGLShaderProgram> shader)
{
	shader->bind();
	std::shared_ptr<Geometry> geometry = mesh->getGeometry();
	std::shared_ptr<PhongMaterial> material = std::dynamic_pointer_cast<PhongMaterial>(mesh->getMaterial());
	if (material == nullptr)
	{
		return;
	}
	geometry->getVAO()->bind();
	material->getTexture()->bind();
	GLuint textid = material->getTexture()->textureId();
	material->getTexture()->bind(textid);
	GLuint specular_map_id = material->getSpecularTexture()->textureId();
	material->getSpecularTexture()->bind(specular_map_id);

	shader->setUniformValue("sampler", material->getTexture()->textureId());
	shader->setUniformValue("specular_map", material->getSpecularTexture()->textureId());
	shader->setUniformValue("modelMatrix", mesh->getModelMatrix());
	shader->setUniformValue("normalMatrix", mesh->getNormalMatrix());	//todo normalMatrix计算没有考虑modeMatrix
	shader->setUniformValue("viewMatrix", camera->getViewMatrix());
	shader->setUniformValue("projectionMatrix", camera->getProjectionMatrix());
	shader->setUniformValue("cameraPos", camera->getCameraPosition());
	shader->setUniformValue("ambientColor", ambient_light->getColor());
	shader->setUniformValue("spotLight.position", spot_light->getPosition());
	shader->setUniformValue("spotLight.color", spot_light->getColor());
	shader->setUniformValue("spotLight.specular_intensity", spot_light->getSpecularIntensity());
	shader->setUniformValue("spotLight.targetDirection", spot_light->getTargetDirection());
	shader->setUniformValue("spotLight.innerLine", spot_light->getInnerAngle());
	shader->setUniformValue("spotLight.outerLine", spot_light->getOuterAngle());
	for (int i = 0; i < directional_lights.size(); i++)
	{
		std::string light_name = "directionalLights[" +std::to_string(i) + "]";
		shader->setUniformValue((light_name + ".direction").c_str(), directional_lights[i].getTargetDirection());
		shader->setUniformValue((light_name+".color").c_str(), directional_lights[i].getColor());
		shader->setUniformValue((light_name+".specular_intensity").c_str(), directional_lights[i].getSpecularIntensity());
	}
}

void Renderer::whiteRender(std::shared_ptr<Mesh> mesh, std::shared_ptr<Camera> camera, std::shared_ptr<QOpenGLShaderProgram> shader)
{
	shader->bind();
	std::shared_ptr<Geometry> geometry = mesh->getGeometry();
	geometry->getVAO()->bind();
	shader->setUniformValue("modelMatrix", mesh->getModelMatrix());
	shader->setUniformValue("viewMatrix", camera->getViewMatrix());
	shader->setUniformValue("projectionMatrix", camera->getProjectionMatrix());

}
