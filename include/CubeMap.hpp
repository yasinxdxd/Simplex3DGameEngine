#ifndef CUBE_MAP_HPP
#define CUBE_MAP_HPP

#include <array>
#include "Vertex.hpp"
#include "Definitions.hpp"
#include "Shader.hpp"
#include "Renderable.hpp"

namespace Simplex3D
{
	class CubeMap : public Renderable
	{
	public:
		explicit CubeMap();
		~CubeMap();

		void bind();
		void unBind();
		bool loadFromFile(const char* file_path[6]);
		virtual void draw(Window& window, Camera cam, glm::mat4 model, Shader& shader, glm::vec3 light_pos) override;
	private:
		int m_width, m_height, m_nr_channels;
		unsigned char* m_data;
	private:
		U32 m_texture;
		U32 VAO, VBO, EBO;
        IndexArray m_indices;
		VertexArray m_vertices = {
            // positions          
            Vertex({-50.0f,  50.0f, -50.0f}),
            Vertex({-50.0f, -50.0f, -50.0f}),
            Vertex({ 50.0f, -50.0f, -50.0f}),
            Vertex({ 50.0f, -50.0f, -50.0f}),
            Vertex({ 50.0f,  50.0f, -50.0f}),
            Vertex({-50.0f,  50.0f, -50.0f}),
                                       
            Vertex({-50.0f, -50.0f,  50.0f}),
            Vertex({-50.0f, -50.0f, -50.0f}),
            Vertex({-50.0f,  50.0f, -50.0f}),
            Vertex({-50.0f,  50.0f, -50.0f}),
            Vertex({-50.0f,  50.0f,  50.0f}),
            Vertex({-50.0f, -50.0f,  50.0f}),
                                       
            Vertex({50.0f, -50.0f, -50.0f}),
            Vertex({50.0f, -50.0f,  50.0f}),
            Vertex({50.0f,  50.0f,  50.0f}),
            Vertex({50.0f,  50.0f,  50.0f}),
            Vertex({50.0f,  50.0f, -50.0f}),
            Vertex({50.0f, -50.0f, -50.0f}),
                                       
            Vertex({-50.0f, -50.0f,  50.0f}),
            Vertex({-50.0f,  50.0f,  50.0f}),
            Vertex({ 50.0f,  50.0f,  50.0f}),
            Vertex({ 50.0f,  50.0f,  50.0f}),
            Vertex({ 50.0f, -50.0f,  50.0f}),
            Vertex({-50.0f, -50.0f,  50.0f}),
                                       
            Vertex({-50.0f,  50.0f, -50.0f}),
            Vertex({ 50.0f,  50.0f, -50.0f}),
            Vertex({ 50.0f,  50.0f,  50.0f}),
            Vertex({ 50.0f,  50.0f,  50.0f}),
            Vertex({-50.0f,  50.0f,  50.0f}),
            Vertex({-50.0f,  50.0f, -50.0f}),
                                       
            Vertex({-50.0f, -50.0f, -50.0f}),
            Vertex({-50.0f, -50.0f,  50.0f}),
            Vertex({ 50.0f, -50.0f, -50.0f}),
            Vertex({ 50.0f, -50.0f, -50.0f}),
            Vertex({-50.0f, -50.0f,  50.0f}),
            Vertex({ 50.0f, -50.0f,  50.0f})
        };
	private:
		//Shader m_shader;
	};
}

#endif //CUBE_MAP_HPP