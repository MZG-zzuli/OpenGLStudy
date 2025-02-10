#include "geometry.h"

Geometry::Geometry()
{
}

Geometry::Geometry(QVector<GLfloat> positions, QVector<GLfloat> normals, QVector<GLfloat> uvs, QVector<GLuint> indices, std::shared_ptr<QOpenGLShaderProgram> shader)
{
	vao_ = std::make_shared<QOpenGLVertexArrayObject>();
	vao_->create();
	vao_->bind();

	pos_vbo_ = std::make_shared<QOpenGLBuffer>();
	pos_vbo_->create();
	pos_vbo_->bind();
	pos_vbo_->allocate(positions.data(), sizeof(GLfloat)*positions.size());
	//box->glEnableVertexAttribArray(0);
	//box->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	GLuint posIdx = shader->attributeLocation("aPos");
	shader->enableAttributeArray(0);
	shader->setAttributeBuffer(0, GL_FLOAT, 0, 3);


	uv_vbo_ = std::make_shared<QOpenGLBuffer>();
	uv_vbo_->create();
	uv_vbo_->bind();
	uv_vbo_->allocate((const void*)uvs.data(), sizeof(GLfloat)*uvs.size());
	shader->enableAttributeArray(1);
	shader->setAttributeBuffer(1, GL_FLOAT, 0, 2);

	nor_vbo_ = std::make_shared<QOpenGLBuffer>();
	nor_vbo_->create();
	nor_vbo_->bind();
	nor_vbo_->allocate(normals.data(), sizeof(GLfloat)*normals.size());
	GLuint ind = shader->attributeLocation("aNormal");
	shader->enableAttributeArray(2);
	shader->setAttributeBuffer(2, GL_FLOAT, 0, 3);


	ebo_ = std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer);
	ebo_->create();
	ebo_->bind();
	ebo_->allocate((const void*)indices.data(), sizeof(GLuint)*indices.size());
	num_vertices_ = indices.size();
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

QMatrix4x4 Geometry::getTransform()
{
	transform_.rotate(5, QVector3D(0, 1, 0));
	return transform_;
}

QMatrix3x3 Geometry::getNormalMatrix() const
{
	return transform_.inverted().transposed().normalMatrix();
}

GLuint Geometry::getNumVertices() const
{
	return num_vertices_;
}

std::shared_ptr<Geometry> Geometry::createBox(float size, std::shared_ptr<QOpenGLShaderProgram> shader)
{
	std::shared_ptr<Geometry> box = std::make_shared<Geometry>();

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
	float normals[] = {		//法线向量
		//前面
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		//后面
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		//上面
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		//下面
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		//右面
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//左面
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
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
	box->vao_ = std::make_shared<QOpenGLVertexArrayObject>();
	box->vao_->create();
	box->vao_->bind();

	box->pos_vbo_ = std::make_shared<QOpenGLBuffer>();
	box->pos_vbo_->create();
	box->pos_vbo_->bind();
	box->pos_vbo_->allocate(positions, sizeof(positions));
	//box->glEnableVertexAttribArray(0);
	//box->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	GLuint posIdx=shader->attributeLocation("aPos");
	shader->enableAttributeArray(0);
	shader->setAttributeBuffer(0, GL_FLOAT, 0, 3);


	box->uv_vbo_ = std::make_shared<QOpenGLBuffer>();
	box->uv_vbo_->create();
	box->uv_vbo_->bind();
	box->uv_vbo_->allocate(uvs, sizeof(uvs));
	//box->glEnableVertexAttribArray(1);
	//box->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	shader->enableAttributeArray(1);
	shader->setAttributeBuffer(1, GL_FLOAT, 0, 2);

	box->nor_vbo_ = std::make_shared<QOpenGLBuffer>();
	box->nor_vbo_->create();
	box->nor_vbo_->bind();
	box->nor_vbo_->allocate(normals, sizeof(normals));
	GLuint ind = shader->attributeLocation("aNormal");
	shader->enableAttributeArray(2);
	shader->setAttributeBuffer(2, GL_FLOAT, 0, 3);


	//box->texture_->bind();


	box->ebo_ = std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer);
	box->ebo_->create();
	box->ebo_->bind();
	box->ebo_->allocate(indices, sizeof(indices));


	return box;
}

std::shared_ptr<Geometry> Geometry::createSphere(float size, std::shared_ptr<QOpenGLShaderProgram> shader)
{
	std::shared_ptr<Geometry> sphere = std::make_shared<Geometry>();

	int num_lat_lines = 360;
	int num_long_lines = 360;
	std::vector<GLfloat> positions;
	std::vector<GLfloat> uvs;
	std::vector<GLuint> indices;
	std::vector<GLfloat> normals;
	for (int i = 0; i <= num_lat_lines; i++)
	{
		for (int j = 0; j <= num_long_lines; j++)
		{
			float x = size * sin(i * M_PI / num_lat_lines) * cos(j * 2 * M_PI / num_long_lines);
			float y = size * cos(i * M_PI / num_lat_lines);
			float z = size * sin(i * M_PI / num_lat_lines) * sin(j * 2 * M_PI / num_long_lines);
			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
			float u = 1.0 - j * 1.0f / num_long_lines;
			float v = 1.0 - i * 1.0f / num_lat_lines;
			uvs.push_back(u);
			uvs.push_back(v);
		}
	}
	for (int i = 0; i < num_lat_lines; i++)
	{
		for (int j = 0; j < num_long_lines; j++)
		{
			int first = (i * (num_long_lines + 1)) + j;
			int second = (i * (num_long_lines + 1)) + j + 1;
			int third = ((i + 1) * (num_long_lines + 1)) + j + 1;
			int fourth = ((i + 1) * (num_long_lines + 1)) + j;
			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(third);
			indices.push_back(first);
			indices.push_back(third);
			indices.push_back(fourth);
		}
	}
	sphere->vao_ = std::make_shared<QOpenGLVertexArrayObject>();
	sphere->vao_->create();
	sphere->vao_->bind();
	sphere->pos_vbo_ = std::make_shared<QOpenGLBuffer>();
	sphere->pos_vbo_->create();
	sphere->pos_vbo_->bind();
	sphere->pos_vbo_->allocate(positions.data(), positions.size() * sizeof(GLfloat));
	shader->enableAttributeArray(0);
	shader->setAttributeBuffer(0, GL_FLOAT, 0, 3);

	sphere->uv_vbo_ = std::make_shared<QOpenGLBuffer>();
	sphere->uv_vbo_->create();
	sphere->uv_vbo_->bind();
	sphere->uv_vbo_->allocate(uvs.data(), uvs.size() * sizeof(GLfloat));
	shader->enableAttributeArray(1);
	shader->setAttributeBuffer(1, GL_FLOAT, 0, 2);

	sphere->nor_vbo_ = std::make_shared<QOpenGLBuffer>();
	sphere->nor_vbo_->create();
	sphere->nor_vbo_->bind();
	sphere->nor_vbo_->allocate(normals.data(), normals.size() * sizeof(GLfloat));
	shader->enableAttributeArray(2);
	shader->setAttributeBuffer(2, GL_FLOAT, 0, 3);

	sphere->ebo_ = std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer);
	sphere->ebo_->create();
	sphere->ebo_->bind();
	sphere->ebo_->allocate(indices.data(), indices.size() * sizeof(GLuint));
	sphere->num_vertices_ = indices.size();
	return sphere;
}
