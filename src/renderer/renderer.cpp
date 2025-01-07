#include "renderer/renderer.h"



Renderer::Renderer()
{
	initializeOpenGLFunctions();
	phone_shader_ = createShader("resource/vertex.glsl", "resource/fragment.glsl");
}

Renderer::~Renderer()
{
}

void Renderer::render(std::vector<Mesh>& meshs, std::shared_ptr<Camera> camera_, 
	std::shared_ptr<DirectionalLight> directional_light, std::shared_ptr<AmbientLight> ambient_light)
{
	camera_->updataCameraPosition();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < meshs.size(); i++)
	{
		Mesh& mesh=meshs[i];
		std::shared_ptr<QOpenGLShaderProgram> shader = pickShader(mesh.getMaterial()->getMaterialType());
		if (shader == nullptr)
		{
			continue;
		}
		if (mesh.getMaterial()->getMaterialType() == MaterialType::PhongMaterial)
		{
			phongRender(mesh, camera_, directional_light, ambient_light, shader);
		}
		glDrawElements(GL_TRIANGLES, mesh.getGeometry()->getNumVertices(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::phongRender(Mesh& mesh, std::shared_ptr<Camera> camera_,
	std::shared_ptr<DirectionalLight> directional_light, std::shared_ptr<AmbientLight> ambient_light, 
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

	shader->setUniformValue("sampler", material->getTexture()->textureId());
	shader->setUniformValue("transform", geometry->getTransform());
	shader->setUniformValue("modelMatrix", mesh.getModelMatrix());
	shader->setUniformValue("normalMatrix", geometry->getNormalMatrix());
	shader->setUniformValue("viewMatrix", camera_->getViewMatrix());
	shader->setUniformValue("projectionMatrix", camera_->getProjectionMatrix());
	shader->setUniformValue("lightvec", directional_light->getDirection());
	shader->setUniformValue("lightCol", directional_light->getColor());
	shader->setUniformValue("cameraPos", camera_->getCameraPosition());
	shader->setUniformValue("specularIntensity", directional_light->getSpecularIntensity());
	shader->setUniformValue("ambientColor", ambient_light->getColor());

}

std::shared_ptr<QOpenGLShaderProgram> Renderer::createShader(QString vertex_shader_file, QString fragment_shader_file)
{
	std::shared_ptr<QOpenGLShader> vertex_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
	vertex_shader->compileSourceFile(vertex_shader_file);
	std::shared_ptr<QOpenGLShader> fragment_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
	fragment_shader->compileSourceFile(fragment_shader_file);
	std::shared_ptr<QOpenGLShaderProgram> shader_program = std::make_shared<QOpenGLShaderProgram>();
	shader_program->addShader(vertex_shader.get());
	shader_program->addShader(fragment_shader.get());
	shader_program->link();
	return shader_program;
}

std::shared_ptr<QOpenGLShaderProgram> Renderer::pickShader(MaterialType type)
{
	if (type == MaterialType::PhongMaterial)
	{
		return phone_shader_;
	}
	return nullptr;
}
