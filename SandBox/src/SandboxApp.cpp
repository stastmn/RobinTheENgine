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
	//RTE::GameObject spot;
	RTE::GameObject ogre;
	//RTE::GameObject blub;

	float ambientStrength = 1;
	DirectX::XMFLOAT3 ambientColor = DirectX::XMFLOAT3(1, 1, 1);

	float diffuseStrength = 1;
	DirectX::XMFLOAT3 diffuseCollor = DirectX::XMFLOAT3(1, 1, 1);

	DirectX::XMFLOAT3 lightPos = DirectX::XMFLOAT3(0, 0, 0);

	float specularStrength = 0;
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

		//spot.Initialize("objects\\spot\\spot.obj", *RTE::Application::Get().cbuffer);
		//spot.SetTexturePath(0, 0, "objects\\spot\\spot_texture.png");
		//spot.SetPosition(-6, 0.5, 0);
		//spot.SetLookAtPos(XMFLOAT3(0, 0, 1));


		ogre.Initialize("objects\\ogre\\bs_rest.obj", *RTE::Application::Get().cbuffer);
		ogre.SetTexturePath(0, 0, "objects\\ogre\\diffuse.png");

		/*	blub.Initialize("objects\\blub\\blub_triangulated.obj", *RTE::Application::Get().cbuffer);
			blub.SetTexturePath(0, 0, "objects\\blub\\blub_texture.png");
			blub.AdjustPosition(5, 0, 0);*/


	}

	void OnUpdate() override
	{
		timer.Reset();
		timer.Tick();
		//RTE_INFO("ExampleLayer::Delta time {0}",timer.DeltaTime());

		UpdateCamera();
		UpdateLight();

		//ogre.SetLookAtPos(XMFLOAT3(camera->GetPositionFloat3().x * -1, camera->GetPositionFloat3().y * -1, camera->GetPositionFloat3().z *-1));
		//ogre.SetLookAtPos(camera->GetPositionFloat3());
		if (RTE::Input::IsKeyPressed(RTE_KEY_TAB))
			RTE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		static bool attachLightToCamera = false;
		ImGui::Begin("Test");
		if (ImGui::CollapsingHeader("Camera settings")) {

			ImGui::SliderFloat("Camera sensitivity", &cameraSensitivity, 0, 5000);
			ImGui::SliderFloat("Camera speed", &cameraSpeed, 1500, 15000);
		}
		if (ImGui::CollapsingHeader("Light settings"))
		{

			if (ImGui::CollapsingHeader("Ambient"))
			{
				ImGui::DragFloat("Ambient strength", &ambientStrength, 0.01f, 0, 1);
				ImGui::Separator();
				ImGui::ColorPicker3("Ambient color", &ambientColor.x);
			}
			ImGui::Separator();
			if (ImGui::CollapsingHeader("Diffuse"))
			{
				ImGui::DragFloat("Diffuse strength", &diffuseStrength, 0.01f, 0, 1);
				ImGui::Separator();
				ImGui::DragFloat("Specular strength", &specularStrength, 0.01f, 0, 1);
				ImGui::Separator();
				ImGui::ColorPicker3("Diffuse color", &diffuseCollor.x);
				ImGui::Separator();
				ImGui::DragFloat3("Light position", &lightPos.x, 1, -100, 100);
				ImGui::Separator();
				ImGui::Text("Set light position on camera");
				ImGui::SameLine();
				if (ImGui::Button("light")) {
					this->lightPos = camera->GetPositionFloat3();
				}
				ImGui::SameLine();
				ImGui::Checkbox("", &attachLightToCamera);

			}
			ImGui::Separator();
		}

		if (attachLightToCamera) {
			this->lightPos = camera->GetPositionFloat3();
		}
		//ImGui::ShowDemoWindow();
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
		auto vp = camera->GetViewMatrix()* camera->GetProjectionMatrix();
		//spot.Draw(vp);
		ogre.Draw(vp);
		//blub.Draw(vp);
	}

	void UpdateCamera() {
		//window->SetEventCallback()

		if (RTE::Input::IsMouseButtonPressed(RTE_MOUSE_BUTTON_2)) {

			float signX, signY;
			float offsetX = posX - RTE::Input::GetMouseX();
			float offsetY = posY - RTE::Input::GetMouseY();

			signX = offsetX > 0 ? -1 : 1;
			signY = offsetY > 0 ? -1 : 1;

			if (offsetX) {
				camera->AdjustRotation(XMFLOAT3(0, cameraSensitivity* -offsetX * timer.DeltaTime(), 0));
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
			camera->AdjustPosition(XMFLOAT3(0.f, -cameraSpeed * timer.DeltaTime(), 0.f));
		}
	}
	void UpdateLight() {
		RTE::Application::Get().lightCbuffer->data.ambientStrength = this->ambientStrength;
		RTE::Application::Get().lightCbuffer->data.ambientLightColor = this->ambientColor;

		RTE::Application::Get().lightCbuffer->data.diffuseStrenght = this->diffuseStrength;
		RTE::Application::Get().lightCbuffer->data.diffuseCollor = this->diffuseCollor;

		RTE::Application::Get().lightCbuffer->data.lightPosition = this->lightPos;

		RTE::Application::Get().lightCbuffer->data.specularStrength = this->specularStrength;
		RTE::Application::Get().lightCbuffer->data.viewPosition = this->camera->GetPositionFloat3();

		RTE::Application::Get().lightCbuffer->WriteBuffer();
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
