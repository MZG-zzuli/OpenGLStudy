#include "../include/geometry.h"

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

std::shared_ptr<QOpenGLShaderProgram> Geometry::getShaderProgram()
{
	return shader_program_;
}

std::shared_ptr<QOpenGLVertexArrayObject> Geometry::getVAO()
{
	return vao_;
}

std::shared_ptr<QOpenGLTexture> Geometry::getTexture()
{
	return texture_;
}

GLuint Geometry::getNumVertices() const
{
	return num_vertices_;
}

std::shared_ptr<Geometry> Geometry::createBox(float size)
{
	std::shared_ptr<Geometry> box = std::make_shared<Geometry>();
	std::shared_ptr<QOpenGLShader> vertex_shader_ = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
	vertex_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/vertex.glsl");
	std::shared_ptr<QOpenGLShader> fragment_shader_ = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
	fragment_shader_->compileSourceFile("E:/QtProject/GLStudy/resource/fragment.glsl");
	box->shader_program_ = std::make_shared<QOpenGLShaderProgram>();
	box->shader_program_->addShader(vertex_shader_.get());
	box->shader_program_->addShader(fragment_shader_.get());
	box->shader_program_->link();
	box->shader_program_->bind();

	float halfSize = size / 2.0f;
	box->num_vertices_ = 36;
	float positions[] = {
		// Front face
		-halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, halfSize, halfSize, halfSize, -halfSize, halfSize, halfSize,
		// Back face
		-halfSize, -halfSize, -halfSize, -halfSize, halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, -halfSize, -halfSize,
		// Top face
		-halfSize, halfSize, halfSize, halfSize, halfSize, halfSize, halfSize, halfSize, -halfSize, -halfSize, halfSize, -halfSize,
		// Bottom face
		-halfSize, -halfSize, -halfSize, halfSize, -halfSize, -halfSize, halfSize, -halfSize, halfSize, -halfSize, -halfSize, halfSize,
		// Right face
		halfSize, -halfSize, halfSize, halfSize, -halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, halfSize, halfSize,
		// Left face
		-halfSize, -halfSize, -halfSize, -halfSize, -halfSize, halfSize, -halfSize, halfSize, halfSize, -halfSize, halfSize, -halfSize
	};

	float uvs[] = {
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,   // Front face
		4, 5, 6, 6, 7, 4,   // Back face
		8, 9, 10, 10, 11, 8,  // Top face
		12, 13, 14, 14, 15, 12, // Bottom face
		16, 17, 18, 18, 19, 16, // Right face
		20, 21, 22, 22, 23, 20  // Left face
	};
	box->vao_= std::make_shared<QOpenGLVertexArrayObject>();
	box->vao_->create();
	box->vao_->bind();

	box->pos_vbo_= std::make_shared<QOpenGLBuffer>();
	box->pos_vbo_->create();
	box->pos_vbo_->bind();
	box->pos_vbo_->allocate(positions, sizeof(positions));
	//box->glEnableVertexAttribArray(0);
	//box->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	int aPos_location = box->shader_program_->attributeLocation("aPos");
	box->shader_program_->enableAttributeArray(aPos_location);
	box->shader_program_->setAttributeBuffer(aPos_location, GL_FLOAT, 0, 3);

	box->uv_vbo_= std::make_shared<QOpenGLBuffer>();
	box->uv_vbo_->create();
	box->uv_vbo_->bind();
	box->uv_vbo_->allocate(uvs, sizeof(uvs));
	//box->glEnableVertexAttribArray(1);
	//box->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	int aUV_location = box->shader_program_->attributeLocation("uv");
	box->shader_program_->enableAttributeArray(aUV_location);
	box->shader_program_->setAttributeBuffer(aUV_location, GL_FLOAT, 0, 2);

	box->texture_ = std::make_shared<QOpenGLTexture>(QImage("E:/QtProject/GLStudy/resource/1.jpg").mirrored());
	box->texture_->setMinificationFilter(QOpenGLTexture::Nearest);
	box->texture_->setMagnificationFilter(QOpenGLTexture::Linear);
	int texture_id = box->texture_->textureId();
	box->texture_->bind(texture_id);
	//box->texture_->bind();
	box->shader_program_->setUniformValue("sampler", texture_id);


	box->ebo_ = std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer);
	box->ebo_->create();
	box->ebo_->bind();
	box->ebo_->allocate(indices, sizeof(indices));


	return box;
}

std::shared_ptr<Geometry> Geometry::createSphere(float size)
{
	std::shared_ptr<Geometry> sphere = std::make_shared<Geometry>();

	return sphere;
}
