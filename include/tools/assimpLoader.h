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
#include"material/depthMaterial.h"
#include"tools/tools.h"
/*
* aiScence下含有一个根节点(mRootNode)一个材质数组(mMaterials)和一个网格数组(mMeshes)
* 每个节点可以有多个子节点(Node)和多个网格(Mesh)和一个变化矩阵(mTransformation)
* 节点下存网格id，对应mMeshes数组中的网格
* 每个网格可以有多个材质(Material)
*/
class AssimpLoader
{
public:
	static std::shared_ptr<Object> load(const QString& path);
private:
	static std::shared_ptr<Object> porcessNode(aiNode* ai_node, const aiScene* ai_scene, QString& root_path);
	static std::shared_ptr<Mesh> porcessMesh(aiMesh* ai_mesh, const aiScene* ai_scene, QString& root_path);
	static std::shared_ptr<QOpenGLTexture> processTexture(aiMaterial* ai_material, const aiScene* ai_scene, aiTextureType type, QString& root_path);
	static QMatrix4x4 getMat4f(aiMatrix4x4& value);			//将aiMatrix4x4转化为QMatrix4x4

};