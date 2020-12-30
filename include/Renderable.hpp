#ifndef SIMPLEX3D_RENDERABLE_HPP
#define SIMPLEX3D_RENDERABLE_HPP

#include "Camera.hpp"
#include "Shader.hpp"

namespace Simplex3D
{
	class Window;

	class Renderable
	{
	protected:
		virtual void draw(Window& window, Camera cam, glm::mat4 model, Shader& shader) = 0;
	};

}

#endif //SIMPLEX3D_RENDERABLE_HPP
