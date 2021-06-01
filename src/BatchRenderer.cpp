#include "BatchRenderer.hpp"
#include <glad/glad.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.hpp"
#include "Window.hpp"


namespace Simplex3D
{

	BatchRenderer::BatchRenderer()
	{

		m_shader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/batchShaderV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/batchShaderF.glsl");
		m_shader.attachShader();

		//generate VAO:
		glGenVertexArrays(1, &VAO);
		//generate VBO:
		glGenBuffers(1, &VBO);
		//generate EBO:
		glGenBuffers(1, &EBO);
		
		bind();

		setVertices();
		setIndices();
		setup();

		//data:
		//glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Simplex3D::Vertex), m_vertices.data(), GL_STATIC_DRAW);//GL_STATIC_DRAW //GL_DYNAMIC_DRAW
		//data:
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(U16), m_indices.data(), GL_STATIC_DRAW);		
		

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_LINE  GL_FILL GL_POINT
	}

	BatchRenderer::~BatchRenderer()
	{
		unBind();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);

		//delete VAO:
		glDeleteVertexArrays(1, &VAO);
		//delete VBO:
		glDeleteBuffers(1, &VBO);
		//delete EBO:
		glDeleteBuffers(1, &EBO);
	}

	void BatchRenderer::draw(Window& window, Camera cam, glm::mat4 model, glm::vec3 light_pos)
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
		
		//window.getWidth()
		//window.getHeight()




		//all drawing stuff
		m_shader.use();
		m_shader.uniformMatrix4fv("model", 1, false, glm::value_ptr(m_model));
		m_shader.uniformMatrix4fv("view", 1, false, glm::value_ptr(m_view));
		m_shader.uniformMatrix4fv("projection", 1, false, glm::value_ptr(m_projection));

		bind();
			//glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		unBind();
	}

	void BatchRenderer::setVertices()
	{
		m_vertices = {
			//BatchVertex({-1.f,  1.f, 0.f}),//left-up
			//BatchVertex({ 1.f,  1.f, 0.f}),//right-up
			//BatchVertex({-1.f, -1.f, 0.f}),//left-down
			//BatchVertex({ 1.f, -1.f, 0.f}) //right-down
			BatchVertex({-0.5f,  0.5f,  0.5f}),
			BatchVertex({ 0.5f,  0.5f,  0.5f}),
			BatchVertex({-0.5f, -0.5f,  0.5f}),
			BatchVertex({ 0.5f, -0.5f,  0.5f}),
			
			BatchVertex({-0.5f,  0.5f, -0.5f}),
			BatchVertex({ 0.5f,  0.5f, -0.5f}),
			BatchVertex({-0.5f, -0.5f, -0.5f}),
			BatchVertex({ 0.5f, -0.5f, -0.5f}),
			
			BatchVertex({-0.5f,  0.5f,  0.5f}),
			BatchVertex({ 0.5f,  0.5f,  0.5f}),
			BatchVertex({-0.5f,  0.5f, -0.5f}),
			BatchVertex({ 0.5f,  0.5f, -0.5f}),

			BatchVertex({-0.5f, -0.5f,  0.5f}),
			BatchVertex({ 0.5f, -0.5f,  0.5f}),
			BatchVertex({-0.5f, -0.5f, -0.5f}),
			BatchVertex({ 0.5f, -0.5f, -0.5f}),
			
			BatchVertex({ 0.5f, -0.5f,  0.5f}),
			BatchVertex({ 0.5f,  0.5f,  0.5f}),
			BatchVertex({ 0.5f, -0.5f, -0.5f}),
			BatchVertex({ 0.5f,  0.5f, -0.5f}),

			BatchVertex({-0.5f, -0.5f,  0.5f}),
			BatchVertex({-0.5f,  0.5f,  0.5f}),
			BatchVertex({-0.5f, -0.5f, -0.5f}),
			BatchVertex({-0.5f,  0.5f, -0.5f})
			
		};
	}

	void BatchRenderer::setIndices()
	{

		m_indices = {
			0, 1, 2, //first triangle
			2, 3, 1,  //second triangle

			4, 5, 6, //first triangle
			6, 7, 5,  //second triangle

			8, 9, 10, //first triangle
			10, 11, 9,  //second triangle

			12, 13, 14, //first triangle
			14, 15, 13,  //second triangle

			16, 17, 18, //first triangle
			18, 19, 17,  //second triangle

			20, 21, 22, //first triangle
			22, 23, 21,  //second triangle
		};
	}

	void BatchRenderer::setup()
	{
		bind();


		//data:
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(BatchRenderer), m_vertices.data(), GL_STATIC_DRAW);//GL_STATIC_DRAW //GL_DYNAMIC_DRAW
		//data:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(U32), m_indices.data(), GL_DYNAMIC_DRAW);


		//position attribute:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, BatchVertex::position));
		glEnableVertexAttribArray(0);
		//texcoord attribute:
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, BatchVertex::texcoord));
		glEnableVertexAttribArray(1);
		//normal attribute:
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, BatchVertex::normal));
		glEnableVertexAttribArray(2);
		//color attribute:
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, BatchVertex::color));
		glEnableVertexAttribArray(3);
		//texture ID attribute:
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, BatchVertex::textureID));
		glEnableVertexAttribArray(4);


		unBind();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_LINE  GL_FILL GL_POINT
	}

	void BatchRenderer::bind()
	{
		//bind VAO:
		glBindVertexArray(VAO);
		//bind VBO:
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//bind EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void BatchRenderer::unBind()
	{
		//unbind EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//unbind VBO:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//unbind VAO:
		glBindVertexArray(0);
	}
}