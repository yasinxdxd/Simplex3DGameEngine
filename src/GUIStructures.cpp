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

		entity->setPosition({ pos[0], pos[1], pos[2] });
		entity->setScale({ scale[0], scale[1], scale[2] });
		entity->setRotateX(rotation[0]);
		entity->setRotateY(rotation[1]);
		entity->setRotateZ(rotation[2]);
		
	}

	void Transform::render()
	{

		ImGui::Begin("Transform: ");
		ImGui::DragFloat3("Position: ", pos);
		ImGui::DragFloat3("Scale: ", scale);
		ImGui::DragFloat3("Rotation: ", rotation);
		ImGui::End();

	}

	ColorPicker::ColorPicker()
	{ }

	ColorPicker::~ColorPicker()
	{ }
	
	void ColorPicker::update(Entity*& entitiy)
	{
		entitiy->setColor({ color[0],color[1] ,color[2], 1.f });
	}

	void ColorPicker::render()
	{

		ImGui::Begin("ColorPicker: ");
		ImGui::ColorPicker3("Color: ", color);
		ImGui::End();

	}

	EntityGUI::EntityGUI()
	{
		this->selected = false;
	}
	EntityGUI::~EntityGUI()
	{ }

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
			if (eg->selected)
			{
				eg->entity->update();
				eg->transform.update(eg->entity);
				eg->colorPicker.update(eg->entity);
			}
		}
	}

	void ComponentList::render()
	{

		ImGui::Begin("Entities:", 0, ImGuiWindowFlags_MenuBar );

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("1.Menu"))
				{
					menu1 = true;
					menu2 = false;
				ImGui::EndMenu();
				}
				
				if(ImGui::BeginMenu("2.Menu"))
				{
					menu2 = true;
					menu1 = false;
				ImGui::EndMenu();
				}

			ImGui::EndMenuBar();
			}
				
			if (menu1)
			{
				ImGui::Text("Hello");
			}
			if (menu2)
			{
				ImGui::Button("Add Entity +", ImVec2(120.f, 40.f));
				ImGui::BeginChild("...", ImVec2(256, 400), true);
					for (U16 i = 0; i < entityGUIs.size(); i++)
						ImGui::Selectable(entityGUIs[i]->name.c_str(), &entityGUIs[i]->selected, 1, ImVec2(256, 32));
				
				ImGui::EndChild();
			}

		ImGui::End();
		

		for (auto eg : entityGUIs)
		{
			if (eg->selected)
			{
				eg->transform.render();
				eg->colorPicker.render();
			}
		}


	}

	void ComponentList::addEntity(Entity& entity, std::string name)
	{
		entityGUIs.push_back(new EntityGUI());
		entityGUIs[entityGUIs.size() - 1]->entity = &entity;
		entityGUIs[entityGUIs.size() - 1]->name = name;
	}

	MenuBar::MenuBar()
	{
		
	}
	
	MenuBar::~MenuBar()
	{

	}

	void MenuBar::render()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if(ImGui::BeginMenu("File", true))
			{
				//
				//
			ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{

				ImGui::MenuItem("abcd", NULL, true);
				ImGui::MenuItem("gdghgfh", NULL, true);
				ImGui::MenuItem("vcbcvb", NULL, false);
				ImGui::MenuItem("ýoouou jkhjkh", NULL, false);
				ImGui::MenuItem("merhahas", NULL, false);
				ImGui::MenuItem("g fdgf df", NULL, false);
				ImGui::MenuItem("fsdfsdf", NULL, false);
				ImGui::MenuItem("yhfjhgj g dgf df", NULL, true);
				
			ImGui::EndMenu();
			}
		ImGui::EndMainMenuBar();
		}
	}
}