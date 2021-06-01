#include "LOD.hpp"
#include "Definitions.hpp"

namespace priv
{
	const constexpr U16 WIDTH = 200;
	const constexpr U16 HEIGHT = 200;


	LOD::LOD()
	{
		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderF.glsl");
		m_shader.attachShader();
	}

	LOD::~LOD()
	{
	}

	void LOD::generate()
	{
		IndexArray indices;
		VertexArray vertices;

		for (U16 x = 0; x < WIDTH; x++)
		{
			for (U16 z = 0; z < HEIGHT; z++)
			{
				
				vertices.push_back(Simplex3D::Vertex({x, 0, z}));
				vertices.push_back(Simplex3D::Vertex({x + 1, 0, z}));
				vertices.push_back(Simplex3D::Vertex({x, 0, z + 1}));
				vertices.push_back(Simplex3D::Vertex({x + 1, 0, z}));
				vertices.push_back(Simplex3D::Vertex({x, 0, z + 1}));
				vertices.push_back(Simplex3D::Vertex({x + 1, 0, z + 1}));
			}
		}

		m_meshes.push_back(Shared<Simplex3D::Mesh>(new Simplex3D::Mesh(vertices, indices)));
	}

}
