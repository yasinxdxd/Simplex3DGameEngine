#include "CubeMap.hpp"
#include <glad/glad.h>
#include "stb_image.h"
#include "Log.hh"
#include "Window.hpp"

namespace Simplex3D
{

	CubeMap::CubeMap()
	{
		//texture parameters
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		//generate VAO:
		glGenVertexArrays(1, &VAO);
		//generate VBO:
		glGenBuffers(1, &VBO);
		//generate EBO:
		glGenBuffers(1, &EBO);

		bind();


		//data:
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Simplex3D::Vertex), m_vertices.data(), GL_STATIC_DRAW);//GL_STATIC_DRAW //GL_DYNAMIC_DRAW
		//data:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(U32), m_indices.data(), GL_STATIC_DRAW);


		//position attribute:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simplex3D::Vertex), (void*)offsetof(Simplex3D::Vertex, Simplex3D::Vertex::position));
		glEnableVertexAttribArray(0);

		unBind();
		
	}

	CubeMap::~CubeMap()
	{
		unBind();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		//delete VAO:
		glDeleteVertexArrays(1, &VAO);
		//delete VBO:
		glDeleteBuffers(1, &VBO);
		//delete EBO:
		glDeleteBuffers(1, &EBO);

		//delete texture
		glDeleteTextures(sizeof(unsigned int), &m_texture);
	}

	void CubeMap::bind()
	{
		//bind VAO:
		glBindVertexArray(VAO);
		//bind VBO:
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//bind EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void CubeMap::unBind()
	{
		//unbind EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//unbind VBO:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//unbind VAO:
		glBindVertexArray(0);
	}

	bool CubeMap::loadFromFile(const char* file_path[6])
	{
		for (U32 i = 0; i < 6; i++)
		{
			m_data = stbi_load(file_path[i], &m_width, &m_height, &m_nr_channels, 0);
			if (m_data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
				stbi_image_free(m_data);
			}
			else
			{
				log("Failed to load texture! %s", file_path[i]);
				stbi_image_free(m_data);
				return false;
			}	
		}

		return true;
	}

	void CubeMap::draw(Window& window, Camera cam, glm::mat4 model, Shader& shader, glm::vec3 light_pos)
	{
		glm::mat4 m_model = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);
		glm::mat4 m_projection = glm::mat4(1.0f);

		m_projection = glm::perspective(glm::radians(45.f), (float)window.getWidth() / (float)window.getHeight(), 1.5f, 1500000.0f);
		m_view = cam.view;//glm::mat4(glm::mat3(cam.view));
		m_model = model;

		m_model[3][0] = cam.position.x;
		m_model[3][1] = cam.position.y;
		m_model[3][2] = cam.position.z;

		shader.use();
		// ... set view and projection matrix
		shader.uniformMatrix4fv("model", 1, false, glm::value_ptr(m_model));
		shader.uniformMatrix4fv("view", 1, false, glm::value_ptr(m_view));
		shader.uniformMatrix4fv("projection", 1, false, glm::value_ptr(m_projection));


		glDepthMask(GL_FALSE);
		bind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		unBind();
		glDepthMask(GL_TRUE);

	}

}