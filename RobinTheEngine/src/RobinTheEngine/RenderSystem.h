#pragma once
namespace RTE {

	class RenderSystem
	{
	public:
		virtual void Init() = 0;
		virtual void OnResize(int width, int height) = 0;
		virtual void OnRender() = 0;
		virtual ~RenderSystem() = default;

	};

}

