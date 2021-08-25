#include <iostream>
#include <RTE.h>
#include "imgui/imgui.h"

using namespace DirectX;

class ExampleLayer : public RTE::Layer
{
public:

	RTE::Camera* camera;
	RTE::Window* window;
	GameTimer timer;
	float cameraSensitivity;
	float posX, posY;
	float cameraSpeed;


	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnAttach() {

		camera = &RTE::Application::Get().camera;
		camera->SetPosition(XMFLOAT3(0, 0, -10));
		camera->SetProjectionProperties(90, static_cast<float>(RTE::Application::Get().GetWindow().GetWidth()) / static_cast<float>(RTE::Application::Get().GetWindow().GetWidth()), 0.05, 1000);
		window = &RTE::Application::Get().GetWindow();
		cameraSensitivity = 40;
		cameraSpeed = 1500;

	}

	void OnUpdate() override
	{
		timer.Reset();
		timer.Tick();
		//RTE_INFO("ExampleLayer::Delta time {0}",timer.DeltaTime());

		UpdateCamera();


		if (RTE::Input::IsKeyPressed(RTE_KEY_TAB))
			RTE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Camera settings:");
		ImGui::SliderFloat("Camera sensitivity", &cameraSensitivity, 0, 1000);
		ImGui::SliderFloat("Camera speed", &cameraSpeed, 1500, 8000);
		ImGui::End();
	}

	void OnEvent(RTE::Event& event) override
	{
		RTE_TRACE("{0}", event);
		RTE::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<RTE::MouseButtonPressedEvent>(std::bind(&ExampleLayer::SetMousePosition, this, std::placeholders::_1));
		dispatcher.Dispatch<RTE::MouseButtonReleasedEvent>(std::bind(&ExampleLayer::ShowCursor, this, std::placeholders::_1));
		//RTE_ASSERT(false, "Its false!");

	}


	void OnRender()override
	{
	}

	void UpdateCamera() {
		//window->SetEventCallback()

		if (RTE::Input::IsMouseButtonPressed(RTE_MOUSE_BUTTON_2)) {

			float signX,signY;
			float offsetX = posX - RTE::Input::GetMouseX();
			float offsetY = posY - RTE::Input::GetMouseY();

			signX = offsetX > 0 ? -1 : 1;
			signY = offsetY > 0 ? -1 : 1;

			if (offsetX) {
				camera->AdjustRotation(XMFLOAT3(0, cameraSensitivity* -offsetX  * timer.DeltaTime(), 0));
				posX = RTE::Input::GetMouseX();
			}
			if (offsetY) {
				camera->AdjustRotation(XMFLOAT3(cameraSensitivity * -offsetY * timer.DeltaTime(), 0, 0));
				posY = RTE::Input::GetMouseY();
			}

		}
		
		if (RTE::Input::IsKeyPressed(RTE_KEY_W)) {
			camera->AdjustPosition(camera->GetForwardVector() * cameraSpeed* timer.DeltaTime());
		}
		if (RTE::Input::IsKeyPressed(RTE_KEY_S)) {
			camera->AdjustPosition(camera->GetBackwardVector() * cameraSpeed* timer.DeltaTime());
		}
		if (RTE::Input::IsKeyPressed(RTE_KEY_A)) {
			camera->AdjustPosition(camera->GetLeftVector() * cameraSpeed* timer.DeltaTime());
		}
		if (RTE::Input::IsKeyPressed(RTE_KEY_D)) {
			camera->AdjustPosition(camera->GetRightVector() * cameraSpeed* timer.DeltaTime());
		}
		if (RTE::Input::IsKeyPressed(RTE_KEY_SPACE)) {
			camera->AdjustPosition(XMFLOAT3(0.f, cameraSpeed* timer.DeltaTime(), 0.f));
		}
		if (RTE::Input::IsKeyPressed(RTE_KEY_LEFT_CONTROL)) {
			camera->AdjustPosition(XMFLOAT3(0.f, -cameraSpeed* timer.DeltaTime(), 0.f));
		}
	}

	bool SetMousePosition(RTE::MouseButtonPressedEvent ev) {
		if (ev.GetMouseButton() == RTE_MOUSE_BUTTON_2) {
			window->HideCursor();
			posX = RTE::Input::GetMouseX();
			posY = RTE::Input::GetMouseY();
		}
		return true;

	}

	bool ShowCursor(RTE::MouseButtonReleasedEvent ev) {
		if (ev.GetMouseButton() == RTE_MOUSE_BUTTON_2) {
			window->ShowCursor();
		}
		return true;

	}
};

class Sandbox : public RTE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};


RTE::Application* RTE::CreateApplication()
{
	return new Sandbox();
}
