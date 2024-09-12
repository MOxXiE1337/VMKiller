#include <vmkui/Application.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace vmkui
{
	Application::Application() : m_initialized(false), m_window(nullptr), m_windowTitle(), m_clearColor()
	{

	}

	void Application::setClearColor(const std::array<float, 4>& color)
	{
		m_clearColor = color;
	}

	const char* Application::getWindowTitle()
	{
		return m_windowTitle.c_str();
	}

	void Application::setWindowTitle(const char* title)
	{
		m_windowTitle = title;
	}

	void Application::init(ApplicationInfo& info)
	{
		if (!glfwInit())
			throw vmkutils::Exception("vmkui: Failed to initialize GLFW", _ApplicationError::GLFW_INIT_FAIL);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		GLFWwindow* window = glfwCreateWindow(info.width, info.height, info.title, nullptr, nullptr);

		if(window == nullptr)
			throw vmkutils::Exception("vmkui: Failed to create GLFW window", _ApplicationError::GLFW_WINDOW_CREATE_FAIL);

		m_window = window;

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // vsync

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		onInit(); // callback

		m_initialized = true;
	}

	void Application::shutdown()
	{
		if (m_initialized)
			throw vmkutils::Exception("vmkui: Application is not initialized!", _ApplicationError::APPLICATION_NOT_INITIALIZED);

		onShutdown(); // callback

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(m_window));
		glfwTerminate();

		m_initialized = false;
	}

	void Application::runMainLoop()
	{
		if(!m_initialized)
			throw vmkutils::Exception("vmkui: Application is not initialized!", _ApplicationError::APPLICATION_NOT_INITIALIZED);

		ImGuiIO& io = ImGui::GetIO();
		GLFWwindow* window = reinterpret_cast<GLFWwindow*>(m_window);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
            {
                ImGui_ImplGlfw_Sleep(10);
                continue;
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

			onRender(); // callback

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            glfwSwapBuffers(window);
        }
	}
}