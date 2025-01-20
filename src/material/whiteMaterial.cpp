#include "material/whiteMaterial.h"
std::once_flag WhiteMaterial::shader_program_flag_;
WhiteMaterial::WhiteMaterial()
{
	type_ = MaterialType::WhiteMaterial;
}

WhiteMaterial::~WhiteMaterial()
{
}

std::shared_ptr<QOpenGLShaderProgram> WhiteMaterial::getShaderProgram()
{
	static std::shared_ptr<QOpenGLShaderProgram> shader_program = std::make_shared<QOpenGLShaderProgram>();
	std::call_once(shader_program_flag_, [=]() {
		std::shared_ptr<QOpenGLShader> vertex_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
		vertex_shader->compileSourceFile("resource/shaders/whiteShader/vertex.glsl");
		std::shared_ptr<QOpenGLShader> fragment_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
		fragment_shader->compileSourceFile("resource/shaders/whiteShader/fragment.glsl");
		shader_program->addShader(vertex_shader.get());
		shader_program->addShader(fragment_shader.get());
		{
			shader_program->link();
		}
		});
	return shader_program;
}
