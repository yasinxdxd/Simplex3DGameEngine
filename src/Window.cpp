#include "Window.hpp"
#include "WindowEvent.hpp"
#include <thread>
#include <sstream>


namespace Simplex3D
{

	Window::Window(U16 width, U16 height, const char* title, bool is_fullscreen):
	m_width(width), m_height(height), m_title(title), m_fullscreen(is_fullscreen)
	{
		m_color = { 0, 0, 0, 1 };
		m_is_open = Init();
		m_delta = 1;
		m_FPS = 120;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool Window::Init()
	{
		//glfw init:
		if (!glfwInit())
		{
			std::cerr << "glfw couldn't initialize!" << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if(m_fullscreen)
			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), glfwGetPrimaryMonitor(), NULL);
		else
			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

		//window init:
		if (!m_window)
		{
			std::cerr << "window couldn't initialize." << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_window);


		//glad init:
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "glad couldn't initialize!" << std::endl;
			return false;
		}


		//int x = 800, y = 250, w = 800, h = 450;
		glViewport(0, 0, m_width, m_height);
		glEnable(GL_DEPTH_TEST);

		return true;
	}


	//Setters:

	void Window::setColor(short r, short g, short b)
	{
		m_color.r = (float)r/255;
		m_color.g = (float)g/255;
		m_color.b = (float)b/255;
		m_color.a = (float)1;
	}

	void Window::setWindowClose(bool value)
	{
		m_is_open = !value;
	}

	//Getters:

	U16 Window::getWidth() const
	{
		return m_width;
	}

	U16 Window::getHeight() const
	{
		return m_height;
	}

	GLFWwindow* Window::getGLFWwindow() const
	{
		return m_window;
	}


	//Others:

	void Window::pollEvent()
	{
		m_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		glfwPollEvents();
		m_is_open = glfwWindowShouldClose(m_window) == 1 ? false : true;

		glfwSetFramebufferSizeCallback(m_window, WindowEvent::framebuffer_size_callback);
		glfwSetWindowSizeCallback(m_window, WindowEvent::window_size_callback);
		glfwSetKeyCallback(m_window, WindowEvent::Keyboard::key_callback);
		
		std::stringstream ss;
		ss << "Simplex3D" << " " << "0.01" << " [" << float(m_delay) << " FPS]";

		glfwSetWindowTitle(m_window, ss.str().c_str());

	}

	bool Window::isOpen()
	{
		return m_is_open;
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(m_color.r, m_color.g, m_color.b, m_color.a);
	}

	void Window::display()
	{
		glfwSwapBuffers(m_window);
		m_delay = (1000 / m_FPS) - m_delta;
		if (m_delay > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((int(m_delay))));
			//std::cout << 1000 / m_delta << std::endl;
		}

		m_delta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - m_start;
	}


}
