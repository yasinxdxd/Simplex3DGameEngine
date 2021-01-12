#include "GUIStructures.hpp"
#include "EngineGUI.hpp"
#include "Window.hpp"

namespace Simplex3D
{

	EngineGUI* EngineGUI::m_instance = nullptr;

	EngineGUI::EngineGUI()
	{

	}

	void EngineGUI::Init(Window& window)
	{

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");


		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		ImGui::StyleColorsLight();
	}

	EngineGUI::~EngineGUI()
	{
		delete m_instance;
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EngineGUI::update()
	{
		componentList.update();
	}

	void EngineGUI::render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		///////////////////////////////////////////////////////
		componentList.render();
		///////////////////////////////////////////////////////
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	EngineGUI* EngineGUI::getInstace() noexcept
	{
		m_instance = m_instance == nullptr ? new EngineGUI : m_instance;
		return m_instance;
	}

}