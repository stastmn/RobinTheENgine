#include "rtepch.h"
#include "Application.h"
#include "Display.h"

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
		Display display(hinst);
		display.Init();
		MSG msg = { 0 };
		while (GetMessage(&msg, 0, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

}
