#include "Entity.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Log.hh"

namespace Simplex3D
{

	Entity::Entity() :
	m_model_matrix(glm::mat4(1.f))
	{ }

	Entity::~Entity()
	{ 
		log("entity has been destroyed!");
		//for (auto m : m_meshes)
			//delete m;
	}
	

	//setters:
	void Entity::setTexture(Texture2D& texture)
	{
		for (auto& m : m_meshes)
			m->setTexture(texture);
	}

	void Entity::setPosition(glm::vec3 position)
	{
		m_model_matrix = glm::translate(m_model_matrix, position);
	}

	void Entity::setRotation(float angle, glm::vec3 rotation)
	{
		m_model_matrix = glm::rotate(m_model_matrix, glm::radians(angle), rotation);
	}

	void Entity::setScale(glm::vec3 scale)
	{
		m_model_matrix = glm::scale(m_model_matrix, scale);
	}

	void Entity::setColor(glm::vec4 color)
	{
		m_shader.use();
		m_shader.uniform4f("fast_color", color.r, color.g, color.b, color.a);
	}

	void Entity::setRotateX(float angle)
	{
		m_model_matrix = glm::rotate(m_model_matrix, glm::radians(angle), glm::vec3(1, 0, 0));
	}

	void Entity::setRotateY(float angle)
	{
		m_model_matrix = glm::rotate(m_model_matrix, glm::radians(angle), glm::vec3(0, 1, 0));
	}

	void Entity::setRotateZ(float angle)
	{
		m_model_matrix = glm::rotate(m_model_matrix, glm::radians(angle), glm::vec3(0, 0, 1));
	}

	void Entity::setScaleX(float scale)
	{
		m_model_matrix = glm::scale(m_model_matrix, glm::vec3(scale, 0, 0));
	}

	void Entity::setScaleY(float scale)
	{
		m_model_matrix = glm::scale(m_model_matrix, glm::vec3(0, scale, 0));
	}

	void Entity::setScaleZ(float scale)
	{
		m_model_matrix = glm::scale(m_model_matrix, glm::vec3(0, 0, scale));
	}

	//getters:
	glm::vec3 Entity::getPosition() const
	{
		return glm::vec3(m_model_matrix[3][0], m_model_matrix[3][1], m_model_matrix[3][2]);
	}
	
	glm::vec3 Entity::getScale() const
	{
		return glm::vec3(m_model_matrix[0][0], m_model_matrix[1][1], m_model_matrix[2][2]);
	}

	glm::vec4 Entity::getColor() const
	{
		return m_meshes[0]->getVertices()[0].color;
	}

	float Entity::getRotateX() const
	{
		return asinf(m_model_matrix[1][2]) * 180 / glm::pi<float>();
	}

	float Entity::getRotateY() const
	{
		return asinf(m_model_matrix[2][0]) * 180 / glm::pi<float>();
	}

	float Entity::getRotateZ() const
	{
		return asinf(m_model_matrix[0][1]) * 180 / glm::pi<float>();
	}

	float Entity::getScaleX() const
	{
		return m_model_matrix[0][0];
	}

	float Entity::getScaleY() const
	{
		return m_model_matrix[1][1];
	}

	float Entity::getScaleZ() const
	{
		return m_model_matrix[2][2];
	}
	
	std::vector<Shared<Simplex3D::Mesh>> Entity::getMeshes() const
	{
		return m_meshes;
	}

	void Entity::drawMeshes(Window& window, Camera cam, glm::vec3 light_pos)
	{
		for (auto& m : m_meshes)
			m->draw(window, cam, m_model_matrix, m_shader, light_pos);
	}


}