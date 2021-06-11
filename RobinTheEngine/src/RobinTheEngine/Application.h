#pragma once
#include "Core.h"
#include "Window.h"

#include "Platform//DirectX12/DirectXRenderSystem.h"

#include "RobinTheEngine/LayerStack.h"
#include "RobinTheEngine/Events/Event.h"
#include "RobinTheEngine/Events/ApplicationEvent.h"


namespace RTE {

	class RTE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline RenderSystem* GetRenderSystem() { return m_RenderSystem.get(); }
		inline static Application& Get() { return *s_Instance; }


	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<RenderSystem> m_RenderSystem;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

	};

	Application* CreateApplication();
}

