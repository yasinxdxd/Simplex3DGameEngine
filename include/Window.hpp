#ifndef SIMPLEX3D_WINDOW_HPP
#define SIMPLEX3D_WINDOW_HPP

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Definitions.hpp"
#include "glm/vec4.hpp"

namespace Simplex3D
{
	class Window
	{
	public:
		explicit Window(U16 width, U16 height, const char* title, bool is_fullscreen = false);
		~Window();

		operator GLFWwindow*() { return m_window; }

		//Setters:
		void setColor(short r, short g, short b);
		void setWindowClose(bool value);

		//Getters:
		U16 getWidth() const;
		U16 getHeight() const;
		GLFWwindow* getGLFWwindow() const;

		//Others:
		void pollEvent();
		bool isOpen();
		void clear();
		void display();

	private:
		bool Init();

	private:
		GLFWwindow* m_window;
		U16 m_width, m_height;
		std::string m_title;
		bool m_is_open;
		glm::vec4 m_color;
		bool m_fullscreen;

	private:
		float m_start;
		float m_delay;
		float m_delta;
		float m_FPS;
		

	};

}

#endif //SIMPLEX3D_WINDOW_HPP