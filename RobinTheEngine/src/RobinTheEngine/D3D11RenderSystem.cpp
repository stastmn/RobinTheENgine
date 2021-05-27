#include "rtepch.h"
#include "D3D11RenderSystem.h"
#include "d3dUtils.h"

using namespace D3DUtils;

namespace RTE {





	D3D11RenderSystem::D3D11RenderSystem(HWND hwnd, int h, int w) : m_hwnd(hwnd), height(h), width(w)
	{

	}

	void D3D11RenderSystem::Init()
	{
		HRESULT res;

		DXGI_SWAP_CHAIN_DESC swapDesc = {};
		swapDesc.BufferCount = 2;
		swapDesc.BufferDesc.Width = width;
		swapDesc.BufferDesc.Height = width;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = m_hwnd;
		swapDesc.Windowed = true;
		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;


		Microsoft::WRL::ComPtr<ID3D11Device> device;

		D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
		res = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG,
			featureLevel,
			1,
			D3D11_SDK_VERSION,
			&swapDesc,
			&m_swapChain,
			&device,
			nullptr,
			&m_context);

		ThrowIfFailed(res);

		ID3D11Texture2D* backTex;
		res = m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backTex);	ThrowIfFailed(res);
		res = device->CreateRenderTargetView(backTex, nullptr, &m_rtv);			ThrowIfFailed(res);

		m_swapChain->QueryInterface<IDXGISwapChain1>(&m_swapChain1);

		m_context->QueryInterface(IID_ID3DUserDefinedAnnotation, (void**)&m_annotation);

		ID3D11Debug* debug;
		device->QueryInterface(IID_ID3D11Debug, (void**)& debug);

	}

}
