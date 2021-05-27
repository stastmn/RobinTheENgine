#include "rtepch.h"
#include "Application.h"
#include "Display.h"
#include "DirectXRenderSystem.h"
#include "Platform/Windows/WindowsWindow.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>


namespace RTE {

	RTE::Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		HINSTANCE hinst = GetModuleHandleW(NULL);
		WindowProps props;
		WindowsWindow window(props);
		auto a = window.GetWindow();

		DirectXRenderSystem renderSystem(glfwGetWin32Window(a));
		renderSystem.Init();

		MSG msg = { 0 };
		while (GetMessage(&msg, 0, 0, 0)) {
			renderSystem.Render();
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

}
