#pragma once

#ifdef RTE_PLATFORM_WINDOWS

extern RTE::Application* RTE::CreateApplication();

int main(int argc, char** argv) 
{
	RTE::Log::Init();
	RTE_TRACE("Hello");
	RTE_INFO("World");
	RTE_WARN("WARN");
	RTE_ERROR("ERROR");

	auto app = RTE::CreateApplication();
	app->Run();
	delete app;
}

#endif
