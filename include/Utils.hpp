#ifndef SIMPLEX3D_UTILS_HPP
#define SIMPLEX3D_UTILS_HPP

#include <string>
#include <vector>
#include <glm/vec3.hpp>


namespace Simplex3D
{
	struct Vertex;
	class Entity;

	class Utils
	{
	public:
		Utils() = delete;

		static std::string loadShaderFromFile(const char* file_path);
		static std::vector<Vertex> loadOBJ(const char* file_path);
		static std::vector<Vertex> loadOBJ2(const char* file_name);
		static void loadOBJEBO(const char* file_path, std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices);
		static glm::vec3 readGyroscope(const char* file_path);
		static void rayCastingMouse(Entity& entity);
	};
}

#endif //SIMPLEX3D_UTILS_HPP