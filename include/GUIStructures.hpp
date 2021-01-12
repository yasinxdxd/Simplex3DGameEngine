#ifndef GUI_STRUCTURES_HPP
#define GUI_STRUCTURES_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Definations.hpp"
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

	struct EntityGUI
	{
		//EntityGUI() { transform = new Transform(); }
		//~EntityGUI() { delete transform; }

		bool selected;
		std::string name;
		Entity* entity;
		Transform transform;
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

		//friend Transform;
	};
}


#endif //GUI_STRUCTURES_HPP