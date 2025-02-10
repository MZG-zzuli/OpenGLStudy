#include"material/textureManager.h"
#include<iostream>
std::map<QString, std::shared_ptr<QOpenGLTexture>> TextureManager::texture_cache_;
std::shared_ptr<QOpenGLTexture> TextureManager::createTexture(QString path)
{
	if (texture_cache_[path] == nullptr)
	{
		texture_cache_[path] = std::make_shared<QOpenGLTexture>(QImage(path).mirrored());
	}
	return texture_cache_[path];
}

std::shared_ptr<QOpenGLTexture> TextureManager::createTextureFromMemory(QString path, const aiTexture* ai_texture)
{
	if (texture_cache_[path] == nullptr)
	{
		QImage image;
		if (ai_texture->mHeight == 0)
		{
			image.loadFromData((const uchar*)ai_texture->pcData, ai_texture->mWidth);
		}
		else
		{
			QImage::Format format;
			if (strcmp(ai_texture->achFormatHint, "rgba8888") == 0)
			{
				format = QImage::Format_RGBA8888;
			}
			else if (strcmp(ai_texture->achFormatHint, "argb8888")==0)
			{
				format = QImage::Format_ARGB32;
			}
			else
			{
				std::cout << "create texture error" << std::endl;
				return nullptr;
			}
			image = QImage((const uchar*)ai_texture->pcData, ai_texture->mWidth, ai_texture->mHeight, format);
		}
		texture_cache_[path] = std::make_shared<QOpenGLTexture>(image.mirrored());
	}
	return texture_cache_[path];
}
