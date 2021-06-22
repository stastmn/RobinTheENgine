#include <iostream>
#include <RTE.h>
#include "imgui/imgui.h"



class ExampleLayer : public RTE::Layer
{
public:
	GameTimer timer;
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnAttach() {

	}

	void OnUpdate() override
	{
		timer.Reset();
		timer.Tick();
		//RTE_INFO("ExampleLayer::Delta time {0}",timer.DeltaTime());
		if (RTE::Input::IsKeyPressed(RTE_KEY_TAB))
			RTE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(RTE::Event& event) override
	{
		RTE_TRACE("{0}", event);
		RTE::EventDispatcher dispatcher(event);
		//RTE_ASSERT(false, "Its false!");

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
