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
		HINSTANCE hinst = GetModuleHandle(NULL);
		Display* display = new Display(hinst, 800, 800);
		display->Init();

		MSG message;
		while (GetMessage(&message, nullptr, 0, 0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

}
