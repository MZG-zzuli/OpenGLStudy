#pragma once
#include<memory>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include"object.h"
#include"geometry.h"
#include"mesh.h"
#include"material/phongMaterial.h"
#include"material/whiteMaterial.h"
#include"tools/tools.h"
class AssimpLoader
{
public:
	static std::shared_ptr<Object> load(const QString& path);
private:
	static std::shared_ptr<Object> porcessNode(aiNode* ai_node, const aiScene* ai_scene, QString& root_path);
	static std::shared_ptr<Mesh> porcessMesh(aiMesh* ai_mesh, const aiScene* ai_scene, QString& root_path);
	static std::shared_ptr<QOpenGLTexture> processTexture(aiMaterial* ai_material, const aiScene* ai_scene, aiTextureType type, QString& root_path);
	static QMatrix4x4 getMat4f(aiMatrix4x4& value);

};