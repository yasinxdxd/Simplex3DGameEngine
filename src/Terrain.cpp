#include "Terrain.hpp"
#include "PerlinNoise.hpp"
constexpr double X_ADD = 0.008;
constexpr double Z_ADD = 0.008;
const constexpr U16 WIDTH = 900;
const constexpr U16 HEIGHT = 900;


namespace Simplex3D
{

	Terrain::Terrain()
	{
		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/shaderF.glsl");
		m_shader.attachShader();
		
		IndexArray indices;
		VertexArray vertices;
		std::vector<double> zOffsets;
		std::vector<double> xOffsets;
		zOffsets.resize(HEIGHT);
		xOffsets.resize(WIDTH);

		double y = 0;
		
		double kz = 0.008;
		double kx = 0.008;
		
		
		double xoffset = 189.0;
		for (U16 x = 0; x < WIDTH; x++)
		{
			double zoffset = 456.0;
			for (U16 z = 0; z < HEIGHT; z++)
			{	
				zoffset += kz;
				zOffsets[z] = zoffset;
			}
			xoffset += kx;
			xOffsets[x] = xoffset;
		}



		
		for (U16 x = 1; x < WIDTH-1; x++)
		{
			//y = mym::perlinNoise2D(xoffset, yoffset) * 100;//r-u
			for (U16 z = 1; z < HEIGHT-1; z++)
			{
				
				y = mym::perlinNoise2D(xOffsets[x-1], zOffsets[z-1]) * 100;
				glm::vec3 a = { x, y + 100, z };

				
				y = mym::perlinNoise2D(xOffsets[x], zOffsets[z-1]) * 100;//l-u
				glm::vec3 b = { x + 1, y + 100, z };

				
				y = mym::perlinNoise2D(xOffsets[x-1], zOffsets[z]) * 100;//r-u		
				glm::vec3 c = { x, y + 100, z + 1 };

				
				y = mym::perlinNoise2D(xOffsets[x], zOffsets[z]) * 100;//r-u		
				glm::vec3 d = { x + 1, y + 100, z + 1 };
				
				Vertex v1(a, { 0,0 }, glm::normalize(glm::cross(b - a, c - a)), { 0.76, 0.69, 0.5, 1 });
				Vertex v2(b, { 0,0 }, glm::normalize(glm::cross(b - a, c - a)), { 0.76, 0.69, 0.5, 1 });
				Vertex v3(c, { 0,0 }, glm::normalize(glm::cross(b - a, c - a)), { 0.76, 0.69, 0.5, 1 });
				Vertex v4(b, { 0,0 }, glm::normalize(glm::cross(b - a, c - a)), { 0.76, 0.69, 0.5, 1 });//c1 - b1, d - b1
				Vertex v5(c, { 0,0 }, glm::normalize(glm::cross(b - a, c - a)), { 0.76, 0.69, 0.5, 1 });//c - b, d - b
				Vertex v6(d, { 0,0 }, glm::normalize(glm::cross(b - a, c - a)), { 0.76, 0.69, 0.5, 1 });
				vertices.push_back(v1);
				vertices.push_back(v2);
				vertices.push_back(v3);	//l-d
				vertices.push_back(v4);	//r-u
				vertices.push_back(v5); //r-d
				vertices.push_back(v6);	//l-d
				
				
			}
		}








		m_meshes.push_back(new Mesh(vertices, indices));
	}

	Terrain::~Terrain()
	{

	}

}