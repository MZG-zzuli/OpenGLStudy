#include"tools/assimpLoader.h"
#include"material/textureManager.h"
#include"object.h"
#include<iostream>
std::shared_ptr<Object> AssimpLoader::load(const QString& path)
{
	Assimp::Importer importer;
	int lastIndex = path.lastIndexOf("/");
	QString root_path = path.mid(0, lastIndex + 1);
	//此处由Assimp::Importer析构函数释放内存aiScene*
	const aiScene* ai_scene = importer.ReadFile(path.toStdString(), aiProcess_Triangulate | aiProcess_GenNormals);
	if (ai_scene == nullptr || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || ai_scene->mRootNode == nullptr)
	{
		std::cerr << "Error loading\n";
		return nullptr;
	}
	ai_scene->mRootNode->mTransformation;
	std::shared_ptr<Object> rootNode=std::make_shared<Object>();
	rootNode->addChild(porcessNode(ai_scene->mRootNode, ai_scene,root_path));
	return rootNode;
}

std::shared_ptr<Object> AssimpLoader::porcessNode(aiNode* ai_node, const aiScene* ai_scene, QString& root_path)
{
	std::shared_ptr<Object> object_node = std::make_shared<Object>();
	QMatrix4x4 mat=getMat4f(ai_node->mTransformation);
	object_node->setPosition(Tools::getPosition(mat));
	object_node->setScale(Tools::getScale(mat));
	object_node->setAngle(Tools::getEulerAngle(mat));
	for (unsigned int i = 0; i < ai_node->mNumMeshes; i++)
	{
		unsigned int meshIndex = ai_node->mMeshes[i];
		aiMesh* ai_mesh = ai_scene->mMeshes[meshIndex];
		std::shared_ptr<Mesh> mesh = porcessMesh(ai_mesh, ai_scene, root_path);
		object_node->addChild(mesh);
	}
	for (unsigned int i = 0; i < ai_node->mNumChildren; i++)
	{
		object_node->addChild(porcessNode(ai_node->mChildren[i], ai_scene, root_path));
	}
	return object_node;
}

std::shared_ptr<Mesh> AssimpLoader::porcessMesh(aiMesh* ai_mesh, const aiScene* ai_scene, QString& root_path)
{
	QVector<GLfloat> positions;
	QVector<GLfloat> normals;
	QVector<GLfloat> uvs;
	QVector<GLuint> indices;
	for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
	{
		positions.push_back(ai_mesh->mVertices[i].x);
		positions.push_back(ai_mesh->mVertices[i].y);
		positions.push_back(ai_mesh->mVertices[i].z);

		normals.push_back(ai_mesh->mNormals[i].x);
		normals.push_back(ai_mesh->mNormals[i].y);
		normals.push_back(ai_mesh->mNormals[i].z);

		uvs.push_back(ai_mesh->mTextureCoords[0][i].x);
		uvs.push_back(ai_mesh->mTextureCoords[0][i].y);
	}
	for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < ai_mesh->mFaces[i].mNumIndices; j++)
		{
			indices.push_back(ai_mesh->mFaces[i].mIndices[j]);
		}
	}
	std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(positions, normals, uvs, indices, PhongMaterial::getShaderProgram());
	std::shared_ptr<PhongMaterial> material = std::make_shared<PhongMaterial>();
	if (ai_mesh->mMaterialIndex >= 0)
	{
		aiMaterial* ai_material = ai_scene->mMaterials[ai_mesh->mMaterialIndex];
		std::shared_ptr<QOpenGLTexture> diffuse_texture = processTexture(ai_material, ai_scene, aiTextureType_DIFFUSE, root_path);
		if (diffuse_texture == nullptr)
		{
			diffuse_texture = TextureManager::createTexture("resource/defaultTexture.jpg");
		}
		std::shared_ptr<QOpenGLTexture> specular_texture = processTexture(ai_material, ai_scene, aiTextureType_SPECULAR, root_path);
		if (specular_texture == nullptr)
		{
			specular_texture = TextureManager::createTexture("resource/defaultTexture.jpg");
		}
		material->setTexture(diffuse_texture);
		material->setSpecularTexture(specular_texture);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(geometry, material);
		return mesh;
	}
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(geometry, material);
	return mesh;
}

std::shared_ptr<QOpenGLTexture> AssimpLoader::processTexture(aiMaterial* ai_material, const aiScene* ai_scene, aiTextureType type, QString& root_path)
{
	aiString aipath;
	ai_material->Get(AI_MATKEY_TEXTURE(type, 0), aipath);	//获取第一个贴图路径
	QString path = QString(aipath.data);
	path = path.toLower();		//转为小写，不确定
	if (path.length())
	{
		std::cout<<"load texture:"<<path.toStdString()<<std::endl;
	}
	if (path.length() == 0)
	{
		//没有贴图
		return nullptr;
	}
	//如果时内嵌纹理，此处可以返回对应的纹理
	const aiTexture* ai_texture = ai_scene->GetEmbeddedTexture(aipath.C_Str());
	if (ai_texture)
	{
		return TextureManager::createTextureFromMemory(path, ai_texture);
	}
	else
	{
		return TextureManager::createTexture(root_path + path);
	}


}

QMatrix4x4 AssimpLoader::getMat4f(aiMatrix4x4& value)
{
	QMatrix4x4 mat(
		value.a1, value.a2, value.a3, value.a4,
		value.b1, value.b2, value.b3, value.b4,
		value.c1, value.c2, value.c3, value.c4,
		value.d1, value.d2, value.d3, value.d4
	);
	return mat;
}
