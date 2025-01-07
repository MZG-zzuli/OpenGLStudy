#include "material/phongMaterial.h"

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
