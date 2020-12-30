#include "Entity.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include <iostream>

namespace Simplex3D
{

	Entity::Entity() :
	m_model_matrix(glm::mat4(1.f))
	{ }

	Entity::~Entity()
	{ 
		for (auto m : m_meshes)
			delete m;
	}
	

	//setters:
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
		return glm::vec4(1);
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
	
	std::vector<Simplex3D::Mesh*> Entity::getMeshes() const
	{
		return m_meshes;
	}

}