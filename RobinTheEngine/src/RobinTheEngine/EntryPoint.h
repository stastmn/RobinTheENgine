#pragma once

#ifdef RTE_PLATFORM_WINDOWS

extern RTE::Application* RTE::CreateApplication();

int main(int argc, char** argv) 
{
	RTE::Log::Init();

	auto app = RTE::CreateApplication();
	app->Run();
	delete app;
}

#endif
