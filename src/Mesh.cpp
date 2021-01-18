#include "Mesh.hpp"
#include <glad/glad.h>
#include <string>
#include "Utils.hpp"
#include "Window.hpp"


namespace Simplex3D
{

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices):
		m_vertices(vertices), m_indices(indices)
	{
		//generate VAO:
		glGenVertexArrays(1, &VAO);
		//generate VBO:
		glGenBuffers(1, &VBO);
		//generate EBO:
		glGenBuffers(1, &EBO);

		this->setupMesh();

	}

	Mesh::~Mesh()
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
	}

	void Mesh::bind()
	{
		//bind VAO:
		glBindVertexArray(VAO);
		//bind VBO:
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//bind EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void Mesh::unBind()
	{
		//unbind EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//unbind VBO:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//unbind VAO:
		glBindVertexArray(0);
	}

	void Mesh::setupMesh()
	{
		
		bind();


		//data:
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Simplex3D::Vertex), m_vertices.data(), GL_STATIC_DRAW);//GL_STATIC_DRAW //GL_DYNAMIC_DRAW
		//data:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(U16), m_indices.data(), GL_STATIC_DRAW);


		//position attribute:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simplex3D::Vertex), (void*)offsetof(Simplex3D::Vertex, Simplex3D::Vertex::position));
		glEnableVertexAttribArray(0);
		//texcoord attribute:
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Simplex3D::Vertex), (void*)offsetof(Simplex3D::Vertex, Simplex3D::Vertex::texcoord));
		glEnableVertexAttribArray(1);
		//normal attribute:
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Simplex3D::Vertex), (void*)offsetof(Simplex3D::Vertex, Simplex3D::Vertex::normal));
		glEnableVertexAttribArray(2);
		//color attribute:
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Simplex3D::Vertex), (void*)offsetof(Simplex3D::Vertex, Simplex3D::Vertex::color));
		glEnableVertexAttribArray(3);

		
		unBind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_LINE  GL_FILL GL_POINT
	}

	std::vector<Simplex3D::Vertex> Mesh::getVertices() const
	{
		return m_vertices;
	}

	void Mesh::draw(Window& window, Camera cam, glm::mat4 model, Shader& shader, glm::vec3 light_pos)
	{
		glm::mat4 m_model = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);
		glm::mat4 m_projection = glm::mat4(1.0f);
		
		// a += 0.5;
		//model = glm::translate(model, glm::vec3(0.f, 0.0f, -10.f));
		//model = glm::rotate(model, glm::radians(a), glm::vec3(0.0f, 1.0f, 0.f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		

		//projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		m_projection = glm::perspective(glm::radians(45.f), (float)window.getWidth() / (float)window.getHeight(), 1.5f, 1500000.0f);
		m_view = cam.view;
		m_model = model;



		

		//all drawing stuff
		shader.use();
		shader.uniformMatrix4fv("model", 1, false, glm::value_ptr(m_model));
		shader.uniformMatrix4fv("view", 1, false, glm::value_ptr(m_view));
		shader.uniformMatrix4fv("projection", 1, false, glm::value_ptr(m_projection));
		

		//lightning
		shader.use();
		shader.uniform3f("light_position", light_pos.x, light_pos.y, light_pos.z);
		shader.uniform3fv("view_position", 1, glm::value_ptr(cam.position));
		bind();
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Simplex3D::Vertex), (void*)offsetof(Simplex3D::Vertex, Simplex3D::Vertex::normal));
		glEnableVertexAttribArray(2);
		unBind();



		
		bind();
		//if(m_indices.size() == 0)
			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
		//else
			//glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		unBind();
	}

}