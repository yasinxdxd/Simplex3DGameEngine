#ifndef SIMPLEX3D_WINDOW_EVENT_HPP
#define SIMPLEX3D_WINDOW_EVENT_HPP

#include <GLFW/glfw3.h>

namespace Simplex3D
{
	class WindowEvent
	{
		//callback functions:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			// make sure the viewport matches the new window dimensions; note that width and 
			// height will be significantly larger than specified on retina displays.
			glViewport(0, 0, width, height);
		}

		static void window_size_callback(GLFWwindow* window, int width, int height)
		{

		}
		
	public:
		typedef struct Keyboard
		{
		private:
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				if (key == m_key && action == GLFW_PRESS)
					m_key_is_pressed = true;
				else
					m_key_is_pressed = false;
			}
		public:
			static bool isKeyPressed(int key)
			{
				m_key = key;
				return m_key_is_pressed;
			}

		private:
			static inline int m_key;
			static inline bool m_key_is_pressed;

		friend class Window;
		}Keyboard;

	friend class Window;
	};

}

#endif //SIMPLEX3D_WINDOW_EVENT_HPP