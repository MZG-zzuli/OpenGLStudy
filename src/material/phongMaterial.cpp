#include "material/phongMaterial.h"
std::once_flag PhongMaterial::shader_program_flag_;
std::shared_ptr<QOpenGLShaderProgram> PhongMaterial::getShaderProgram()
{
	static std::shared_ptr<QOpenGLShaderProgram> shader_program = std::make_shared<QOpenGLShaderProgram>();
	//static std::once_flag shader_program_flag1_;
	std::call_once(shader_program_flag_, [=]() {
		std::shared_ptr<QOpenGLShader> vertex_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
		vertex_shader->compileSourceFile("resource/shaders/phongShader/vertex.glsl");
		std::shared_ptr<QOpenGLShader> fragment_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
		fragment_shader->compileSourceFile("resource/shaders/phongShader/fragment.glsl");
		shader_program->addShader(vertex_shader.get());
		shader_program->addShader(fragment_shader.get());
		{
			shader_program->link();
		}
		});
	return shader_program;
}

PhongMaterial::PhongMaterial()
{
	type_ = MaterialType::PhongMaterial;
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::setTexture(std::shared_ptr<QOpenGLTexture> texture)
{
	texture_ = texture;
}

void PhongMaterial::setShiness(GLfloat shiness)
{
	shiness_ = shiness;
}

void PhongMaterial::setTexture(QString texture_path)
{
	texture_ = std::make_shared<QOpenGLTexture>(QImage(texture_path).mirrored());
	texture_->setMinificationFilter(QOpenGLTexture::Nearest);
	texture_->setMagnificationFilter(QOpenGLTexture::Linear);
}

std::shared_ptr<QOpenGLTexture> PhongMaterial::getTexture() const
{
	return texture_;
}

void PhongMaterial::setSpecularTexture(std::shared_ptr<QOpenGLTexture> texture)
{
	specular_texture_ = texture;
}

void PhongMaterial::setSpecularTexture(QString texture_path)
{
	specular_texture_ = std::make_shared<QOpenGLTexture>(QImage(texture_path).mirrored());
	specular_texture_->setMinificationFilter(QOpenGLTexture::Nearest);
	specular_texture_->setMagnificationFilter(QOpenGLTexture::Linear);
}

std::shared_ptr<QOpenGLTexture> PhongMaterial::getSpecularTexture() const
{
	return specular_texture_;
}
