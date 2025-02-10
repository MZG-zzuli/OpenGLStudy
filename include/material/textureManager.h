#pragma once
#include<QOpenGLTexture>
#include<memory>
#include<map>
#include<QString>
#include<assimp/texture.h>
class TextureManager
{
public:
	static std::shared_ptr<QOpenGLTexture> createTexture(QString path);
	static std::shared_ptr<QOpenGLTexture> createTextureFromMemory(QString path, const aiTexture* ai_texture);
private:
	static std::map<QString, std::shared_ptr<QOpenGLTexture>> texture_cache_;
};