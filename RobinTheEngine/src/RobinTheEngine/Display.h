#pragma once
#include <windows.h>
#include <string>

namespace RTE
{


	class Display
	{
	public:
		Display(HINSTANCE hinst, int Width = 800, int Height = 800);
		~Display();
		bool Init();

	private:
		void WndProc();

		HINSTANCE m_Hinst = nullptr; // application instance handle
		HWND      m_HWnd = nullptr; // main window handle

		int m_ClientWidth = 800;
		int m_ClientHeight = 800;
		std::wstring  m_MainWndCaption = L"Game Window";

	};


}

