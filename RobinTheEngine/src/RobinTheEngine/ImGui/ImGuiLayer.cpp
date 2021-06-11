#include "rtepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "GLFW/glfw3.h"
#include "Platform/DirectX12/imgui_impl_glfw.h"
#include "Platform/DirectX12/imgui_impl_win32.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/DirectX12/ImGuiDirectX12Renderer.h"

#include "RobinTheEngine/Application.h"

namespace RTE {

	RTE::WindowsWindow* win;
	RTE::DirectXRenderSystem* ren;
	ImGuiIO io;

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		win = (WindowsWindow*) &(Application::Get().GetWindow());
		ren = (DirectXRenderSystem*)(Application::Get().GetRenderSystem());
		
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = ImGui::GetIO();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(win->GetHwnd());
		ImGui_ImplDX12_Init(ren->GetDevice().Get(), 1,
			DXGI_FORMAT_R8G8B8A8_UNORM, ren->mCbvHeap.Get(),
			ren->mCbvHeap->GetCPUDescriptorHandleForHeapStart(),
			ren->mCbvHeap->GetGPUDescriptorHandleForHeapStart());
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		io = ImGui::GetIO();
		// Start the Dear ImGui frame
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		bool show_demo_window = true;
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		bool show_another_window = true;
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		ImGui::Render();

		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), ren->GetCmdList());

		// Update and Render additional Platform Windows
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		/*{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault(NULL, (void*)ren->GetCmdList());
		}*/

		//g_pSwapChain->Present(1, 0); // Present with vsync
		//g_pSwapChain->Present(0, 0); // Present without vsync

		/*UINT64 fenceValue = g_fenceLastSignaledValue + 1;
		g_pd3dCommandQueue->Signal(g_fence, fenceValue);
		g_fenceLastSignaledValue = fenceValue;
		frameCtxt->FenceValue = fenceValue;*/
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

	}

}