#ifndef SIMPLEX3D_VERTEX_HPP
#define SIMPLEX3D_VERTEX_HPP

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Simplex3D
{

	struct Vertex
	{
		Vertex( glm::vec3 _position = { 0, 0, 0 },
				glm::vec2 _texcoord = { 0, 0 },
				glm::vec3 _normal = { 0, 0, 0 },
				glm::vec4 _color = { 0.5, 0.5, 0.5, 1 }):
		position(_position), texcoord(_texcoord), normal(_normal), color(_color)
		{ }

		glm::vec3 position;
		glm::vec2 texcoord;
		glm::vec3 normal;
		glm::vec4 color;

	};
	
}


#endif //SIMPLEX3D_VERTEX_HPP
