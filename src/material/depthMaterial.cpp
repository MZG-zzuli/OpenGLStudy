#include"material/depthMaterial.h"
std::once_flag DepthMaterial::shader_program_flag_;
DepthMaterial::DepthMaterial()
{
	type_ = MaterialType::DepthMaterial;
}
DepthMaterial::~DepthMaterial()
{
}
std::shared_ptr<QOpenGLShaderProgram> DepthMaterial::getShaderProgram()
{
	static std::shared_ptr<QOpenGLShaderProgram> shader_program = std::make_shared<QOpenGLShaderProgram>();
	std::call_once(shader_program_flag_, [=]() {
		std::shared_ptr<QOpenGLShader> vertex_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
		vertex_shader->compileSourceFile("resource/shaders/depthShader/vertex.glsl");
		std::shared_ptr<QOpenGLShader> fragment_shader = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
		fragment_shader->compileSourceFile("resource/shaders/depthShader/fragment.glsl");
		shader_program->addShader(vertex_shader.get());
		shader_program->addShader(fragment_shader.get());
		{
			shader_program->link();
		}
		});
	return shader_program;
}
