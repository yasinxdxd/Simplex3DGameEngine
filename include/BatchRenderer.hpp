#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "Definitions.hpp"
#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "Shader.hpp"


namespace Simplex3D
{
	class Camera;
	class Window;

	struct BatchVertex
	{
		BatchVertex(glm::vec3 _position = { 0, 0, 0 },
					glm::vec2 _texcoord = { 0, 0 },
					glm::vec3 _normal = { 0, 0, 0 },
					glm::vec4 _color = { 1, 1, 1, 1 },
					U32 _texID = 0):
					position(_position), texcoord(_texcoord), normal(_normal), color(_color), textureID(_texID)
					{ }
		glm::vec3 position;
		glm::vec2 texcoord;
		glm::vec3 normal;
		glm::vec4 color;
		U32 textureID;
	};
	
	typedef std::vector<BatchVertex> BatchVertexArray;
	typedef std::vector<unsigned int> BatchIndexArray;


	class BatchRenderer
	{
	public:
		BatchRenderer();
		~BatchRenderer();
	public:
		void draw(Window& window, Camera cam, glm::mat4 model, glm::vec3 light_pos);
	private:
		void setVertices();
		void setIndices();
		void setup();
		void bind();
		void unBind();
	private:
		BatchVertexArray m_vertices;
		BatchIndexArray m_indices;
		U32 VAO, VBO, EBO;
		Shader m_shader;
	};

}

#endif //BATCH_RENDERER_HPP