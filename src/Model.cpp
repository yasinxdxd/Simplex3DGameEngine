#include "Model.hpp"
#include <iostream>

namespace Simplex3D
{
	Model::Model()
	{ 
		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderF.glsl");
		m_shader.attachShader();
	}

	Model::Model(const char* file_path)
	{
		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderF.glsl");
		m_shader.attachShader();
		loadModel(file_path);
	}

	Model::~Model()
	{
		
	}


	bool Model::loadModel(const char* file_path)
	{
		//aiProcess_GenSmoothNormals
		std::string file_path_string = file_path;
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(file_path_string, aiProcess_GenSmoothNormals
			| aiProcess_Triangulate
			| aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "The file couldn't successfully opened: " << file_path << std::endl;
			return false;
		}
		m_directory = file_path_string.substr(0, file_path_string.find_last_of('/'));

		if (scene)
			recursiveProcess(scene->mRootNode, scene);
		return true;
	}

	Simplex3D::Mesh* Model::processMesh(const aiMesh* mesh, const aiScene* scene)
	{
	
		//std::vector<Texture> textures;

		//PROCESS VERTICES
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Simplex3D::Vertex vertex;

			//position convert:
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;
			//texcoord convert:
			if (mesh->mTextureCoords[0])
			{
				vertex.texcoord.x = mesh->mTextureCoords[0][i].x;
				vertex.texcoord.y = mesh->mTextureCoords[0][i].y;
			}
			//normal convert:
			if (mesh->mNormals)
			{
				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;
			}
			//color convert:
			if (mesh->mColors[0])
			{
				vertex.color.r = mesh->mColors[0][i].r;
				vertex.color.g = mesh->mColors[0][i].g;
				vertex.color.b = mesh->mColors[0][i].b;
				vertex.color.a = mesh->mColors[0][i].a;
			}

			vertices.push_back(vertex);
		}
		
		////PROCESS INDICES
		for (U16 i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (U16 j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		

		//PROCESS MATERIAL
		if (mesh->mMaterialIndex >= 0)
		{

		}
		
		
		return new Simplex3D::Mesh(vertices, indices);
	}

	void Model::recursiveProcess(aiNode* node, const aiScene* scene)
	{
		//process
		for (U16 i = 0; i < node->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(processMesh(mesh, scene));
		}

		//recursion
		for (U16 i = 0; i < node->mNumChildren; i++)
		{
			recursiveProcess(node->mChildren[i], scene);
		}
	}

	void Model::drawMeshes(Window& window, Camera cam)
	{
		for (auto m : m_meshes)
			m->draw(window, cam, m_model_matrix, m_shader);
	}
	

}