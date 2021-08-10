#pragma once

namespace RTE {
	class DeviceResources
	{
	public:
			virtual void CreateDeviceResources() = 0;
			virtual void CreateWindowSizeDependentResources()= 0;
			virtual bool WindowSizeChanged(int width, int height)= 0;
			virtual void Present()= 0;

		virtual ~DeviceResources() {};
	};
}

