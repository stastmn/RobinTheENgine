#include "rtepch.h"
#include "Application.h"
#include "Display.h"
#include "Platform/DirectX12/DirectX12RenderSystem.h"
#include "Platform/DirectX11/DirectX11RenderSystem.h"
#include "Platform/Windows/WindowsWindow.h"
#include "GLFW/glfw3.h"
#include "RobinTheEngine/Input.h"
#include "Model.h"

#include "Platform/DirectX11/Buffer.h"
#include "Platform/DirectX11/Shaders.h"
#include "Platform/DirectX11/ConstantBuffer.h"
#include "Platform/DirectX11/Vertex.h"
#include "Platform/DirectX11/Camera.h"
#include "Platform/DirectX11/Model.h"


namespace RTE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	RTE::Application::Application()
	{
		RTE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		auto a = ((WindowsWindow*)(m_Window.get()))->GetHwnd();
		m_RenderSystem = std::make_unique<DirectX11RenderSystem>(a);
		m_RenderSystem->Init();
		m_RenderSystem->OnResize(m_Window->GetWidth(), m_Window->GetHeight());


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


	}


	Application::~Application()
	{

	}

	void Application::Run()
	{


		Model model;
		Model model2;

		vertexShader vs(L"shaders\\VS.hlsl");
		pixelShader ps(L"shaders\\PS.hlsl");

		CB_VS_MATRIX4x4 rotation;
		ConstantBuffer<CB_VS_MATRIX4x4> cbuffer;
		model.Initialize("objects\\teapot.obj", cbuffer);
		model2.Initialize("objects\\teapot.obj", cbuffer);
		float i = 5;
		while (m_Running) {
			m_Window->OnUpdate();
			m_RenderSystem->OnRenderBegin();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			for (Layer* layer : m_LayerStack)
				layer->OnRender();


			auto context = static_cast<DirectX11RenderSystem*>(m_RenderSystem.get())->GetContext();
			context->IASetInputLayout(vs.GetInputLayout());
			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			context->VSSetShader(vs.GetShader(), 0, 0);
			context->PSSetShader(ps.GetShader(), 0, 0);

			i += 0.05f;
			context->VSSetConstantBuffers(0, 1, cbuffer.GetAddressOf());
			DirectX::XMStoreFloat4x4(&rotation.matrix, camera.GetViewMatrix()* camera.GetProjectionMatrix());
			cbuffer.WirteBuffer(rotation);

			model.AdjustRotation(0, 0.02 , 0);
			model.Draw(XMLoadFloat4x4(&rotation.matrix));
			model2.SetPosition(sin(i) + 2, cos(i) + 2, 0);
			model2.Draw(XMLoadFloat4x4(&rotation.matrix));

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_RenderSystem->OnRenderEnd();

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		m_RenderSystem->OnResize(e.GetWidth(), e.GetHeight());
		m_RenderSystem->OnResize(800, 800);

		return true;
	}
}
