#pragma once

#include "RobinTheEngine/Layer.h"
#include "RobinTheEngine/Events/ApplicationEvent.h"
#include "RobinTheEngine/Events/MouseEvent.h"
#include "RobinTheEngine/Events/KeyEvent.h"

namespace RTE {

	class RTE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	};

}