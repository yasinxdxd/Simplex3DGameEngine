#ifndef TEXTURE_2D_HPP
#define TEXTURE_2D_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Definitions.hpp"

namespace Simplex3D
{

	class Texture2D
	{
	public:
		explicit Texture2D();
		explicit Texture2D(const char* file_path);

	public:
		bool loadFromFile(const char*);
		//bool loadFrom;
	
	private:
		U16 m_texture;
	};

}

#endif //TEXTURE_2D_HPP
