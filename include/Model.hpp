#ifndef MODEL_HPP
#define MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Entity.hpp"


namespace Simplex3D
{

	class Model : public Entity
	{
	public:
		Model();
		Model(const char* file_path);
		~Model();
	private:
		Simplex3D::Mesh* processMesh(const aiMesh* mesh, const aiScene* scene);
		void recursiveProcess(aiNode* node, const aiScene* scene);

	public:

		
		bool loadModel(const char* file_path);
		
	private:
		std::string m_directory;
		
	
	};

}

#endif //MODEL_HPP
