#pragma once
#include "Core.h"

namespace RTE {

	class RTE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();


	};

	Application* CreateApplication();
}

