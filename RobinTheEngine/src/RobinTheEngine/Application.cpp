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

		vertex_POS_COLLOR vertexArray[] = {

			vertex_POS_COLLOR{ -0.5f, -0.5f, 0, 1.f, 0.f, 0.f, 1.f}, //red
			vertex_POS_COLLOR{ -0.5f, 0.5f,	0, 0, 1, 0, 1} , //green
			vertex_POS_COLLOR{ 0.5f, 0.5f, 0, 0, 0, 1, 1}, //blue
			vertex_POS_COLLOR{ 0.5f, -0.5f, 0, 0, 0, 0, 1 } //black
		};

		DWORD indecies[] = {
			0, 1, 2,
			2, 3, 0
		};

		vertexBuffer<vertex_POS_COLLOR> vertexbuffer(vertexArray, 4);
		IndexBuffer IndexBuffer(indecies, ARRAYSIZE(indecies));

		vertexShader vs(L"shaders\\VS.hlsl");
		pixelShader ps(L"shaders\\PS.hlsl");

		CB_VS_MATRIX4x4 rotation;
		ConstantBuffer<CB_VS_MATRIX4x4> cbuffer;
		float i = 0;
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
			DirectX::XMStoreFloat4x4(&rotation.matrix, DirectX::XMMatrixRotationZ(i));
			cbuffer.WirteBuffer(rotation);

			UINT offset = 0;
			context->IASetVertexBuffers(0, 1, vertexbuffer.GetAdressOf(), vertexbuffer.StridePtr(), &offset);
			context->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			context->DrawIndexed(IndexBuffer.ElementCount(), 0, 0);
			//context->Draw(3, 0);


				/*m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();*/

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
