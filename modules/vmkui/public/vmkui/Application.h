#include <vmkshared/vmk.h>
#include <vmkutils/Noncopyable.h>
#include <vmkutils/Exception.h>

#ifndef __VMKUI_APPLICATION_H__
#define __VMKUI_APPLICATION_H__

namespace vmkui
{
	enum class _ApplicationError
	{
		GLFW_INIT_FAIL,
		GLFW_WINDOW_CREATE_FAIL,
		APPLICATION_NOT_INITIALIZED,
	};

	struct ApplicationInfo
	{
		int width;
		int height;
		const char* title;
	};

	class VMK_API Application : public vmkutils::Noncopyable
	{
	private:
		bool        m_initialized;
		void*       m_window;
		std::string m_windowTitle;
		std::array<float, 4> m_clearColor;
	public:
		Application();

		void        setClearColor(const std::array<float, 4>& color);

		const char* getWindowTitle();
		void        setWindowTitle(const char* title);


		virtual void onInit() {};
		virtual void onShutdown() {};

		virtual void onRender() {};

		void init(ApplicationInfo& info);
		void shutdown();
		void runMainLoop();
	};
}

#endif // __VMKUI_APPLICATION_H__
