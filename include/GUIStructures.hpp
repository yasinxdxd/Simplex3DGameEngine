#ifndef GUI_STRUCTURES_HPP
#define GUI_STRUCTURES_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#include <memory>

#include "Definitions.hpp"
#include "Entity.hpp"

namespace Simplex3D
{

	struct GUI
	{
	protected:
		virtual void render() = 0;
	};

	struct Transform : GUI
	{
		Transform();
		~Transform();

		float pos[3];
		float scale[3];
		float rotation[3];
		
		void update(Entity*& entitiy);
		virtual void render() override;

	};

	struct ColorPicker : GUI
	{
		ColorPicker();
		~ColorPicker();

		float color[3];

		virtual void render() override;
		void update(Entity*& entitiy);
	};

	struct EntityGUI
	{
		EntityGUI();
		~EntityGUI();

		bool selected;
		std::string name;
		Entity* entity;
		Transform transform;
		ColorPicker colorPicker;
	};
	/**
	TO-DO: don't forget to use update func of transform.
	**/

	struct ComponentList : GUI
	{
		ComponentList();
		~ComponentList();

		void update();
		virtual void render() override;
		void addEntity(Entity& entity, std::string name);

	public://private:
		std::vector<EntityGUI*> entityGUIs;
		bool menu1, menu2;
		//friend Transform;
	};


	struct MenuBar : GUI
	{
		MenuBar();
		~MenuBar();
		virtual void render() override;
	};

}


#endif //GUI_STRUCTURES_HPP