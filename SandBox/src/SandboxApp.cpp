#include <iostream>
#include <RTE.h>


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
	}

	void OnEvent(RTE::Event& event) override
	{
		RTE_TRACE("{0}", event);
		RTE::EventDispatcher dispatcher(event);
	
	}


};

class Sandbox : public RTE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new RTE::ImGuiLayer());

	}

	~Sandbox()
	{

	}
};


RTE::Application* RTE::CreateApplication()
{
	return new Sandbox();
}
