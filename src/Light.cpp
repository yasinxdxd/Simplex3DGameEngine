#include "Light.hpp"

namespace Simplex3D
{

	Light::Light()
	{
		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/lightShaderF.glsl");
		m_shader.attachShader();
		std::vector<unsigned int> indices;
		std::vector<Simplex3D::Vertex> vertices = {

		Simplex3D::Vertex({-0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({-0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f, -0.5f}),

		Simplex3D::Vertex({-0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f,  0.5f}),

		Simplex3D::Vertex({-0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f,  0.5f,  0.5f}),

		Simplex3D::Vertex({ 0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f,  0.5f}),

		Simplex3D::Vertex({-0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f, -0.5f, -0.5f}),

		Simplex3D::Vertex({-0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f, -0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({ 0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f,  0.5f,  0.5f}),
		Simplex3D::Vertex({-0.5f,  0.5f, -0.5f}),


		};
	

		m_meshes.push_back(new Mesh(vertices, indices));

	}

	Light::~Light()
	{

	}
}