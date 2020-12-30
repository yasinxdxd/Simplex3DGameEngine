#include "Light.hpp"

namespace Simplex3D
{

	Light::Light()
	{
		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/lightShaderF.glsl");
		m_shader.attachShader();
	}

	Light::~Light()
	{
		
	}
}