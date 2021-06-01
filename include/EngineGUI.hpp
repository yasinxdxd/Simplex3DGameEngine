#ifndef ENGINE_GUI_HPP
#define ENGINE_GUI_HPP


#include "GUIStructures.hpp"

namespace Simplex3D
{
	class Window;

	class EngineGUI
	{
	private:
		EngineGUI();
	public:
		void Init(Window& window);
		~EngineGUI();
	public:
		void update();
		void render();
		static EngineGUI* getInstace() noexcept;


	private:
		void GUIStyle();
		static EngineGUI* m_instance;
		
	public:
		ComponentList componentList;
		MenuBar menuBar;
		

	};

}

#endif //ENGINE_GUI_HPP
