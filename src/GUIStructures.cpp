#include "GUIStructures.hpp"
#include <iostream>
 
namespace Simplex3D
{

	Transform::Transform()
	{
		pos[0] = 0; pos[1] = 0; pos[2] = 0;
		scale[0] = 1; scale[1] = 1; scale[2] = 1;
		rotation[0] = 0; rotation[1] = 0; rotation[2] = 0;
	}

	Transform::~Transform()
	{

	}

	void Transform::update(Entity*& entity)
	{

		entity->update();
		entity->setPosition({ pos[0], pos[1], pos[2] });
		entity->setScale({ scale[0], scale[1], scale[2] });
		entity->setRotateX(rotation[0]);
		entity->setRotateY(rotation[1]);
		entity->setRotateZ(rotation[2]);
		std::cout << pos[0] << std::endl;
		
	}

	void Transform::render()
	{

		ImGui::Begin("Transform: ");
		ImGui::DragFloat3("Position: ", pos);
		ImGui::DragFloat3("Scale: ", scale);
		ImGui::DragFloat3("Rotation: ", rotation);
		ImGui::End();

	}

	ComponentList::ComponentList()
	{

	}

	ComponentList::~ComponentList()
	{
		for (auto eg : entityGUIs)
		{
			delete eg;
		}
	}

	void ComponentList::update()
	{
		for (auto eg : entityGUIs)
		{
			if(eg->selected)
				eg->transform.update(eg->entity);
		}
	}

	void ComponentList::render()
	{

		ImGui::Begin("Entities: ");
		ImGui::Button("Add Entity +", ImVec2(120.f, 40.f));
			ImGui::BeginChild("...", ImVec2(200, 200), true);
			for (U16 i = 0; i < entityGUIs.size(); i++)
				ImGui::Checkbox(entityGUIs[i]->name.c_str(), &entityGUIs[i]->selected);
			ImGui::EndChild();
		ImGui::End();
		

		for (auto eg : entityGUIs)
		{
			if (eg->selected)
				eg->transform.render();
		}


	}

	void ComponentList::addEntity(Entity& entity, std::string name)
	{
		entityGUIs.push_back(new EntityGUI());
		entityGUIs[entityGUIs.size() - 1]->entity = &entity;
		entityGUIs[entityGUIs.size() - 1]->name = name;
	}
}