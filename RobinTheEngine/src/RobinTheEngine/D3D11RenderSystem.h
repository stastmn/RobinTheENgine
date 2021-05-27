#pragma once
#include "RenderSystem.h"

#include "windows.h"
#include <iostream>
#include "winuser.h"
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3d.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <DirectXColors.h>
#include <chrono>
#include <thread>

namespace RTE {

	class D3D11RenderSystem : public RenderSystem
	{
	public:
		D3D11RenderSystem(HWND hwnd, int height = 800, int weight = 800);
		~D3D11RenderSystem();

		void Init() override;


	private:
		ID3D11DeviceContext* m_context;
		IDXGISwapChain* m_swapChain;
		IDXGISwapChain1* m_swapChain1;
		ID3D11RenderTargetView* m_rtv;
		ID3DUserDefinedAnnotation* m_annotation;

		HWND m_hwnd;
	
		int height = 800;
		int width = 800;

	};

}

