#pragma once
#include "RobinTheEngine/DeviceResources.h"
#include "RobinTheEngine/d3dUtils.h"
#include "RobinTheEngine/Log.h"

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif
#include <memory>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

//using namespace DirectX;
//using namespace DX;

using Microsoft::WRL::ComPtr;
//#include "dxgiformat.h"

//namespace RTE {
//	class DirectX11DeviceResources :public RTE::DeviceResources
//	{
//	public:
//
//		/*static const unsigned int c_FlipPresent = 0x1;
//		static const unsigned int c_AllowTearing = 0x2;
//		static const unsigned int c_EnableHDR = 0x4;*/
//
//		
//		DirectX11DeviceResources(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
//			DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT,
//			UINT backBufferCount = 2,
//			D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_10_0,
//			unsigned int flags = 0) noexcept;
//
//
//		virtual void CreateDeviceResources() override;
//		virtual void CreateWindowSizeDependentResources()override;
//		virtual bool WindowSizeChanged(int width, int height)override;
//		virtual void Present()override;
//
//		virtual ~DirectX11DeviceResources() = 0;
//
//		void SetWindow(HWND window, int width, int height);
//		void HandleDeviceLost();
//		//void RegisterDeviceNotify(IDeviceNotify* deviceNotify) { m_deviceNotify = deviceNotify; 
//
//		// Device Accessors.
//		RECT GetOutputSize() const { return m_outputSize; }
//
//		// Direct3D Accessors.
//		ID3D11Device1*          GetD3DDevice() const { return m_d3dDevice.Get(); }
//		ID3D11DeviceContext1*   GetD3DDeviceContext() const { return m_d3dContext.Get(); }
//		IDXGISwapChain1*        GetSwapChain() const { return m_swapChain.Get(); }
//		D3D_FEATURE_LEVEL       GetDeviceFeatureLevel() const { return m_d3dFeatureLevel; }
//		ID3D11Texture2D*        GetRenderTarget() const { return m_renderTarget.Get(); }
//		ID3D11Texture2D*        GetDepthStencil() const { return m_depthStencil.Get(); }
//		ID3D11RenderTargetView*	GetRenderTargetView() const { return m_d3dRenderTargetView.Get(); }
//		ID3D11DepthStencilView* GetDepthStencilView() const { return m_d3dDepthStencilView.Get(); }
//		DXGI_FORMAT             GetBackBufferFormat() const { return m_backBufferFormat; }
//		DXGI_FORMAT             GetDepthBufferFormat() const { return m_depthBufferFormat; }
//		D3D11_VIEWPORT          GetScreenViewport() const { return m_screenViewport; }
//		UINT                    GetBackBufferCount() const { return m_backBufferCount; }
//		DXGI_COLOR_SPACE_TYPE   GetColorSpace() const { return m_colorSpace; }
//		unsigned int            GetDeviceOptions() const { return m_options; }
//
//
//		// Performance events
//		void PIXBeginEvent(_In_z_ const wchar_t* name)
//		{
//			m_d3dAnnotation->BeginEvent(name);
//		}
//
//		void PIXEndEvent()
//		{
//			m_d3dAnnotation->EndEvent();
//		}
//
//		void PIXSetMarker(_In_z_ const wchar_t* name)
//		{
//			m_d3dAnnotation->SetMarker(name);
//		}
//
//	private:
//
//		void CreateFactory();
//		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);
//		void UpdateColorSpace();
//
//		// Direct3D objects.
//		Microsoft::WRL::ComPtr<IDXGIFactory2>               m_dxgiFactory;
//		Microsoft::WRL::ComPtr<ID3D11Device1>               m_d3dDevice;
//		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>        m_d3dContext;
//		Microsoft::WRL::ComPtr<IDXGISwapChain1>             m_swapChain;
//		Microsoft::WRL::ComPtr<ID3DUserDefinedAnnotation>   m_d3dAnnotation;
//
//		// Direct3D rendering objects. Required for 3D.
//		Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_renderTarget;
//		Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_depthStencil;
//		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_d3dRenderTargetView;
//		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_d3dDepthStencilView;
//		D3D11_VIEWPORT                                  m_screenViewport;
//
//		// Direct3D properties.
//		DXGI_FORMAT                                     m_backBufferFormat;
//		DXGI_FORMAT                                     m_depthBufferFormat;
//		UINT                                            m_backBufferCount;
//		D3D_FEATURE_LEVEL                               m_d3dMinFeatureLevel;
//
//		// Cached device properties.
//		HWND                                            m_window;
//		D3D_FEATURE_LEVEL                               m_d3dFeatureLevel;
//		RECT                                            m_outputSize;
//
//		// HDR Support
//		DXGI_COLOR_SPACE_TYPE                           m_colorSpace;
//
//		// DeviceResources options (see flags above)
//		unsigned int                                    m_options;
//
//		// The IDeviceNotify can be held directly as it owns the DeviceResources.
//		//IDeviceNotify*                                  m_deviceNotify;
//
//	};
//}

