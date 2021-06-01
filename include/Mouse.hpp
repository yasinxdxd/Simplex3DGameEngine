#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "glm/vec2.hpp"
#include "GLFW/glfw3.h"

namespace Simplex3D
{

	class Mouse
	{
	public:
		Mouse() = delete;
	
	public:	
		enum MouseButton
		{ Left, Right };

	public:
		static glm::dvec2& getPosition(void);
		static bool isMousePressed(Mouse::MouseButton);
		static bool isMouseReleased(Mouse::MouseButton);
	
	private:
		

	private:
		//returning values
		static inline bool is_mouse_pressed; //static GObool isMousePressed(go::Mouse::MouseButton);
		static inline MouseButton m_button;


	private:
		static inline glm::dvec2 m_position;

	private:
		//callbacks:
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


	friend class Window;
	};

}

#endif //MOUSE_HPP