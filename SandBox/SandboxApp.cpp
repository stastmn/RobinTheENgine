
#include <iostream>
#include <RTE.h>

class Sandbox : public RTE::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};


RTE::Application* RTE::CreateApplication()
{
	return new Sandbox();
}
