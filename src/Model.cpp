#include "Model.hpp"
#include <iostream>
#include <stl_loader.h>
#include "Log.hh"

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


	bool Model::loadModelSTL(const char* file_path)
	{
		STL_HEADER stl_header;
		STL_TRIANGLE* triangles;
		attribute_byte_count* attributes;

		if (!stl_load_from_file(file_path, stl_header, triangles, attributes))
		{
			log("model cannot loaded!");
			return false;
		}

		Simplex3D::Vertex vertex1;
		Simplex3D::Vertex vertex2;
		Simplex3D::Vertex vertex3;
		
		for (U32 i = 0; i < stl_header.triangles_number; i++)
		{
			//position
			vertex1.position.x = triangles[i].vertex1[0];
			vertex1.position.y = triangles[i].vertex1[1];
			vertex1.position.z = triangles[i].vertex1[2];
			vertex2.position.x = triangles[i].vertex2[0];
			vertex2.position.y = triangles[i].vertex2[1];
			vertex2.position.z = triangles[i].vertex2[2];
			vertex3.position.x = triangles[i].vertex3[0];
			vertex3.position.y = triangles[i].vertex3[1];
			vertex3.position.z = triangles[i].vertex3[2];

			//normals:
			vertex1.normal.x = triangles[i].normal_vector[0];
			vertex1.normal.y = triangles[i].normal_vector[1];
			vertex1.normal.z = triangles[i].normal_vector[2];
			vertex2.normal.x = triangles[i].normal_vector[0];
			vertex2.normal.y = triangles[i].normal_vector[1];
			vertex2.normal.z = triangles[i].normal_vector[2];
			vertex3.normal.x = triangles[i].normal_vector[0];
			vertex3.normal.y = triangles[i].normal_vector[1];
			vertex3.normal.z = triangles[i].normal_vector[2];

			//push:
			vertices.push_back(vertex1);
			vertices.push_back(vertex2);
			vertices.push_back(vertex3);
		}

		/*free memory*/
		stl_free<STL_TRIANGLE>(triangles);
		stl_free<attribute_byte_count>(attributes);

		if(triangles)
			log("MEMORY LEAAAAK!");
		if (attributes)
			log("MEMORY LEAAAAK! att");

		m_meshes.push_back(std::make_unique<Mesh>(vertices, indices));

		return true;
	}

	bool Model::loadModelOBJ(const char* file_path)
	{
		
		//std::vector<Vertex> vertices;
		vertices.clear();

		//v,vn,vt values of the .obj files
		std::vector<glm::vec3> position_vertices;
		std::vector<glm::vec2> textcoord_vertices;
		std::vector<glm::vec3> normal_vertices;

		//f values of the .obj files
		std::vector<unsigned int> position_vertices_indices;
		std::vector<unsigned int> textcoord_vertices_indices;
		std::vector<unsigned int> normal_vertices_indices;

		//reading
		std::stringstream ss;
		std::string line = "";
		std::string prefix = "";
		std::fstream file(file_path);

		//temps
		glm::vec3 temp_vec3;
		glm::vec2 temp_vec2;
		unsigned int temp_int;


		//error check
		if (!file.is_open())
			std::cerr << "file couldn't opened!" << std::endl;

		while (std::getline(file, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "#" || prefix == "o" || prefix == "s" || prefix == "g")
				continue;
			else if (prefix == "v")
			{
				ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				position_vertices.push_back(temp_vec3);
			}
			else if (prefix == "vt")
			{
				ss >> temp_vec2.x >> temp_vec2.y;
				textcoord_vertices.push_back(temp_vec2);
			}
			else if (prefix == "vn")
			{
				ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				normal_vertices.push_back(temp_vec3);
			}
			else if (prefix == "f")
			{
				unsigned int counter = 0;
				while (ss >> temp_int)
				{
					if (counter == 0)
						position_vertices_indices.push_back(temp_int);
					else if (counter == 1)
						textcoord_vertices_indices.push_back(temp_int);
					else if (counter == 2)
						normal_vertices_indices.push_back(temp_int);

					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					if (ss.peek() == ' ')
					{
						++counter;
						ss.ignore(1, ' ');
					}

					if (counter > 2)
						counter = 0;
				}

			}
			else
				continue;

		}
		file.close();

		std::cout << position_vertices.size() << std::endl;
		std::cout << textcoord_vertices.size() << std::endl;
		std::cout << normal_vertices.size() << std::endl;

		std::cout << position_vertices_indices.size() << std::endl;
		std::cout << textcoord_vertices_indices.size() << std::endl;
		std::cout << normal_vertices_indices.size() << std::endl;

		vertices.resize(position_vertices_indices.size(), Vertex());

		//setting values of vertex and pushing the vertex in result vertices 
		if ((textcoord_vertices_indices.size() == 0 || textcoord_vertices.size() == 0) &&
			normal_vertices_indices.size() == 0 || normal_vertices.size() == 0)
		{
			for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
			{
				Vertex temp;

				temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
				//temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
				//temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
				temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

				vertices.push_back(temp);
			}
		}
		else if (textcoord_vertices_indices.size() == 0 || textcoord_vertices.size() == 0)
		{
			for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
			{
				Vertex temp;

				temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
				//temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
				temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
				temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

				vertices.push_back(temp);
			}
		}
		else if (normal_vertices_indices.size() == 0 || normal_vertices.size() == 0)
		{
			for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
			{
				Vertex temp;

				temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
				temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
				//temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
				temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

				vertices.push_back(temp);
			}
		}
		else
		{
			for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
			{
				Vertex temp;

				temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
				temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
				temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
				temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

				vertices.push_back(temp);
			}
		}

		
		m_meshes.push_back(std::make_unique<Mesh>(vertices, indices));

		return true;
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

	/*std::unique_ptr<Mesh>*/ Mesh* Model::processMesh(const aiMesh* mesh, const aiScene* scene)
	{
	
		//std::vector<Texture> textures;

		//PROCESS VERTICES
		for (U32 i = 0; i < mesh->mNumVertices; i++)
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
		
		return new Mesh(vertices, indices);
		//return std::make_unique<Simplex3D::Mesh>(vertices, indices);
	}

	void Model::recursiveProcess(aiNode* node, const aiScene* scene)
	{
		//process
		for (U16 i = 0; i < node->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(Shared<Mesh>(processMesh(mesh, scene)));
		}

		//recursion
		for (U16 i = 0; i < node->mNumChildren; i++)
		{
			recursiveProcess(node->mChildren[i], scene);
		}
	}


}