#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Mesh.hpp"
#include <memory>

namespace Simplex3D
{

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

	public:
		void update()
		{ m_model_matrix = glm::mat4(1.f); }

	public:
		virtual void setPosition(glm::vec3);
		virtual void setRotation(float angle, glm::vec3);
		virtual void setScale(glm::vec3);
		virtual void setColor(glm::vec4);
		
		virtual void setTexture(Texture2D& texture);

		virtual void setRotateX(float angle);
		virtual void setRotateY(float angle);
		virtual void setRotateZ(float angle);

		virtual void setScaleX(float scale);
		virtual void setScaleY(float scale);
		virtual void setScaleZ(float scale);

	public:
		virtual glm::vec3 getPosition() const;
		virtual glm::vec3 getScale() const;
		virtual glm::vec4 getColor() const;

		virtual float getRotateX() const;
		virtual float getRotateY() const;
		virtual float getRotateZ() const;

		virtual float getScaleX() const;
		virtual float getScaleY() const;
		virtual float getScaleZ() const;

		std::vector<Shared<Simplex3D::Mesh>> getMeshes() const;

	public:
		virtual void drawMeshes(Window& window, Camera cam, glm::vec3 light_pos);



	protected:
		glm::mat4 m_model_matrix;
		std::vector<Shared<Simplex3D::Mesh>> m_meshes;
		Shader m_shader;

		VertexArray vertices;
		IndexArray indices;


	//friend ComponentList;
	};


}


#endif //ENTITY_HPP
