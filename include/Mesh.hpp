#ifndef SIMPLEX3D_MESH_HPP
#define SIMPLEX3D_MESH_HPP

#include "Definitions.hpp"
#include "Vertex.hpp"
#include "Renderable.hpp"
#include "Texture2D.hpp"
#include <vector>

namespace Simplex3D
{

	class Mesh : public Renderable
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		~Mesh();

	private:
		void bind();
		void unBind();

	public:
		void setupMesh();
		
		std::vector<Simplex3D::Vertex> getVertices() const;
		void setVertices(std::vector<Simplex3D::Vertex> vertices);
		
		virtual void draw(Window& window, Camera cam, glm::mat4 model, Shader& shader, glm::vec3 light_pos) override;

		void setTexture(Texture2D& m_texture);

	private:
		unsigned int VAO, VBO, EBO;
		float a = 0;
		Texture2D m_texture;
		IndexArray m_indices;
		VertexArray m_vertices;
		//std::vector<Simplex3D::Texture> m_textures;

	};

}


#endif //SIMPLEX3D_MESH_HPP