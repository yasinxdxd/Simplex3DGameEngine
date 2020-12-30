#ifndef SIMPLEX3D_MESH_HPP
#define SIMPLEX3D_MESH_HPP

#include "Definations.hpp"
#include "Vertex.hpp"
#include "Renderable.hpp"
#include <vector>

namespace Simplex3D
{

	class Mesh : public Renderable
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<U16> indices);
		~Mesh();
	public:
		void bind();
		void unBind();

		void setupMesh();
		
		std::vector<Simplex3D::Vertex> getVertices() const;
		
		virtual void draw(Window& window, Camera cam, glm::mat4 model, Shader& shader) override;

	private:
		U16 VAO, VBO, EBO;
		float a = 0;
		std::vector<unsigned int> m_indices;
		std::vector<Simplex3D::Vertex> m_vertices;
		//std::vector<Simplex3D::Texture> m_textures;

	};

}

typedef std::vector<Simplex3D::Vertex> VertexArray;
typedef std::vector<unsigned int> IndexArray;

#endif //SIMPLEX3D_MESH_HPP