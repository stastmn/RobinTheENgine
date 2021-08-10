#include "rtepch.h"
//#include "DirectX11DeviceResources.h"
//
//using namespace D3DUtils;
//using Microsoft::WRL::ComPtr;
//
//RTE::DirectX11DeviceResources::DirectX11DeviceResources(
//	DXGI_FORMAT backBufferFormat,
//	DXGI_FORMAT depthBufferFormat,
//	UINT backBufferCount,
//	D3D_FEATURE_LEVEL minFeatureLevel,
//	unsigned int flags) noexcept :
//	m_screenViewport{},
//	m_backBufferFormat(backBufferFormat),
//	m_depthBufferFormat(depthBufferFormat),
//	m_backBufferCount(backBufferCount),
//	m_d3dMinFeatureLevel(minFeatureLevel),
//	m_window(nullptr),
//	m_d3dFeatureLevel(D3D_FEATURE_LEVEL_9_1),
//	m_outputSize{ 0, 0, 1, 1 },
//	m_colorSpace(DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709),
////	m_options(flags | c_FlipPresent)
///*,
//	m_deviceNotify(nullptr)*/
//{
//}
//
//
//void RTE::DirectX11DeviceResources::CreateDeviceResources()
//{
//	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
//
//#if defined(_DEBUG)
//	HRESULT hr = D3D11CreateDevice(
//		nullptr,
//		D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
//		nullptr,
//		D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
//		nullptr,                    // Any feature level will do.
//		0,
//		D3D11_SDK_VERSION,
//		nullptr,                    // No need to keep the D3D device reference.
//		nullptr,                    // No need to know the feature level.
//		nullptr                     // No need to keep the D3D device context reference.
//	);
//	if (hr)
//	{
//		// If the project is in a debug build, enable debugging via SDK Layers with this flag.
//		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
//	}
//	else
//	{
//		RTE_CORE_WARN("WARNING: Direct3D Debug Device is not available\n");
//	}
//#endif
//
//	CreateFactory();
//
//
//	// Determine DirectX hardware feature levels this app will support.
//	static const D3D_FEATURE_LEVEL s_featureLevels[] =
//	{
//		D3D_FEATURE_LEVEL_11_1,
//		D3D_FEATURE_LEVEL_11_0,
//		D3D_FEATURE_LEVEL_10_1,
//		D3D_FEATURE_LEVEL_10_0,
//		D3D_FEATURE_LEVEL_9_3,
//		D3D_FEATURE_LEVEL_9_2,
//		D3D_FEATURE_LEVEL_9_1,
//	};
//
//	UINT featLevelCount = 0;
//	for (; featLevelCount < _countof(s_featureLevels); ++featLevelCount)
//	{
//		if (s_featureLevels[featLevelCount] < m_d3dMinFeatureLevel)
//			break;
//	}
//
//	if (!featLevelCount)
//	{
//		throw std::out_of_range("minFeatureLevel too high");
//	}
//
//	ComPtr<IDXGIAdapter1> adapter;
//	GetHardwareAdapter(adapter.GetAddressOf());
//
//	// Create the Direct3D 11 API device object and a corresponding context.
//	ComPtr<ID3D11Device> device;
//	ComPtr<ID3D11DeviceContext> context;
//
//	//HRESULT hr = E_FAIL;
//	if (adapter)
//	{
//		hr = D3D11CreateDevice(
//			adapter.Get(),
//			D3D_DRIVER_TYPE_UNKNOWN,
//			nullptr,
//			creationFlags,
//			s_featureLevels,
//			featLevelCount,
//			D3D11_SDK_VERSION,
//			device.GetAddressOf(),  // Returns the Direct3D device created.
//			&m_d3dFeatureLevel,     // Returns feature level of device created.
//			context.GetAddressOf()  // Returns the device immediate context.
//		);
//	}
//#if defined(NDEBUG)
//	else
//	{
//		throw std::exception("No Direct3D hardware device found");
//	}
//#else
//	if (FAILED(hr))
//	{
//		// If the initialization fails, fall back to the WARP device.
//		// For more information on WARP, see:
//		hr = D3D11CreateDevice(
//			nullptr,
//			D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
//			nullptr,
//			creationFlags,
//			s_featureLevels,
//			featLevelCount,
//			D3D11_SDK_VERSION,
//			device.GetAddressOf(),
//			&m_d3dFeatureLevel,
//			context.GetAddressOf()
//		);
//
//		if (SUCCEEDED(hr))
//		{
//			RTE_CORE_TRACE("Direct3D Adapter - WARP\n");
//		}
//	}
//#endif
//
//	ThrowIfFailed(hr);
//
//#ifndef NDEBUG
//	ComPtr<ID3D11Debug> d3dDebug;
//	if (SUCCEEDED(device.As(&d3dDebug)))
//	{
//		ComPtr<ID3D11InfoQueue> d3dInfoQueue;
//		if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
//		{
//#ifdef _DEBUG
//			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
//			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
//#endif
//			D3D11_MESSAGE_ID hide[] =
//			{
//				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
//			};
//			D3D11_INFO_QUEUE_FILTER filter = {};
//			filter.DenyList.NumIDs = _countof(hide);
//			filter.DenyList.pIDList = hide;
//			d3dInfoQueue->AddStorageFilterEntries(&filter);
//		}
//	}
//#endif
//
//	ThrowIfFailed(device.As(&m_d3dDevice));
//	ThrowIfFailed(context.As(&m_d3dContext));
//	ThrowIfFailed(context.As(&m_d3dAnnotation));
//
//}
//
//void RTE::DirectX11DeviceResources::CreateWindowSizeDependentResources()
//{
//
//	if (!m_window)
//	{
//		throw std::exception("Call SetWindow with a valid Win32 window handle");
//	}
//
//	// Clear the previous window size specific context.
//	ID3D11RenderTargetView* nullViews[] = { nullptr };
//	m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
//	m_d3dRenderTargetView.Reset();
//	m_d3dDepthStencilView.Reset();
//	m_renderTarget.Reset();
//	m_depthStencil.Reset();
//	m_d3dContext->Flush();
//
//	// Determine the render target size in pixels.
//	UINT backBufferWidth = std::max<UINT>(static_cast<UINT>(m_outputSize.right - m_outputSize.left), 1u);
//	UINT backBufferHeight = std::max<UINT>(static_cast<UINT>(m_outputSize.bottom - m_outputSize.top), 1u);
//	DXGI_FORMAT backBufferFormat =  m_backBufferFormat;
//
////	if (m_swapChain)
////	{
////		// If the swap chain already exists, resize it.
////	/*	HRESULT hr = m_swapChain->ResizeBuffers(
////			m_backBufferCount,
////			backBufferWidth,
////			backBufferHeight,
////			backBufferFormat,
////			(m_options & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u
////		);*/
////
////		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
////		{
////#ifdef _DEBUG
////			char buff[64] = {};
////			sprintf_s(buff, "Device Lost on ResizeBuffers: Reason code 0x%08X\n", (hr == DXGI_ERROR_DEVICE_REMOVED) ? m_d3dDevice->GetDeviceRemovedReason() : hr);
////			OutputDebugStringA(buff);
////#endif
////			// If the device was removed for any reason, a new device and swap chain will need to be created.
////			HandleDeviceLost();
////
////			// Everything is set up now. Do not continue execution of this method. HandleDeviceLost will reenter this method
////			// and correctly set up the new device.
////			return;
////		}
////		else
////		{
////			ThrowIfFailed(hr);
////		}
////	}
//	else
//	{
//		// Create a descriptor for the swap chain.
//		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
//		swapChainDesc.Width = backBufferWidth;
//		swapChainDesc.Height = backBufferHeight;
//		swapChainDesc.Format = backBufferFormat;
//		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//		swapChainDesc.BufferCount = m_backBufferCount;
//		swapChainDesc.SampleDesc.Count = 1;
//		swapChainDesc.SampleDesc.Quality = 0;
//		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
//	//	swapChainDesc.SwapEffect = (m_options & (c_FlipPresent | c_AllowTearing | c_EnableHDR)) ? DXGI_SWAP_EFFECT_FLIP_DISCARD : DXGI_SWAP_EFFECT_DISCARD;
//		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
//		swapChainDesc.Flags = (m_options & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u;
//
//		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
//		fsSwapChainDesc.Windowed = TRUE;
//
//		// Create a SwapChain from a Win32 window.
//		ThrowIfFailed(m_dxgiFactory->CreateSwapChainForHwnd(
//			m_d3dDevice.Get(),
//			m_window,
//			&swapChainDesc,
//			&fsSwapChainDesc,
//			nullptr, m_swapChain.ReleaseAndGetAddressOf()
//		));
//
//		// This class does not support exclusive full-screen mode and prevents DXGI from responding to the ALT+ENTER shortcut
//		ThrowIfFailed(m_dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
//	}
//
//	// Handle color space settings for HDR
//	UpdateColorSpace();
//
//	// Create a render target view of the swap chain back buffer.
//	ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(m_renderTarget.ReleaseAndGetAddressOf())));
//
//	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(D3D11_RTV_DIMENSION_TEXTURE2D, m_backBufferFormat);
//	ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(
//		m_renderTarget.Get(),
//		&renderTargetViewDesc,
//		m_d3dRenderTargetView.ReleaseAndGetAddressOf()
//	));
//
//	if (m_depthBufferFormat != DXGI_FORMAT_UNKNOWN)
//	{
//		// Create a depth stencil view for use with 3D rendering if needed.
//		CD3D11_TEXTURE2D_DESC depthStencilDesc(
//			m_depthBufferFormat,
//			backBufferWidth,
//			backBufferHeight,
//			1, // This depth stencil view has only one texture.
//			1, // Use a single mipmap level.
//			D3D11_BIND_DEPTH_STENCIL
//		);
//
//		ThrowIfFailed(m_d3dDevice->CreateTexture2D(
//			&depthStencilDesc,
//			nullptr,
//			m_depthStencil.ReleaseAndGetAddressOf()
//		));
//
//		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
//		ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(
//			m_depthStencil.Get(),
//			&depthStencilViewDesc,
//			m_d3dDepthStencilView.ReleaseAndGetAddressOf()
//		));
//	}
//
//	// Set the 3D rendering viewport to target the entire window.
//	m_screenViewport = CD3D11_VIEWPORT(
//		0.0f,
//		0.0f,
//		static_cast<float>(backBufferWidth),
//		static_cast<float>(backBufferHeight)
//	);
//
//}
//
//bool RTE::DirectX11DeviceResources::WindowSizeChanged(int width, int height)
//{
//	
//	RECT newRc;
//    newRc.left = newRc.top = 0;
//    newRc.right = width;
//    newRc.bottom = height;
//    if (newRc == m_outputSize)
//    {
//        UpdateColorSpace();
//
//        return false;
//    }
//
//    m_outputSize = newRc;
//    CreateWindowSizeDependentResources();
//    return true;
//}
//
//void RTE::DirectX11DeviceResources::Present()
//{
//
//}
//
//void RTE::DirectX11DeviceResources::SetWindow(HWND window, int width, int height)
//{
//}
//
//void RTE::DirectX11DeviceResources::HandleDeviceLost()
//{
//}
//
//void RTE::DirectX11DeviceResources::CreateFactory()
//{
//#if defined(_DEBUG) && (_WIN32_WINNT >= 0x0603 /*_WIN32_WINNT_WINBLUE*/)
//	bool debugDXGI = false;
//	{
//		ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
//		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
//		{
//			debugDXGI = true;
//
//			ThrowIfFailed(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf())));
//
//			dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
//			dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
//
//			DXGI_INFO_QUEUE_MESSAGE_ID hide[] =
//			{
//				80 /* IDXGISwapChain::GetContainingOutput: The swapchain's adapter does not control the output on which the swapchain's window resides. */,
//			};
//			DXGI_INFO_QUEUE_FILTER filter = {};
//			filter.DenyList.NumIDs = _countof(hide);
//			filter.DenyList.pIDList = hide;
//			dxgiInfoQueue->AddStorageFilterEntries(DXGI_DEBUG_DXGI, &filter);
//		}
//	}
//
//	if (!debugDXGI)
//#endif
//
//		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf())));
//}
//
//void RTE::DirectX11DeviceResources::GetHardwareAdapter(IDXGIAdapter1 ** ppAdapter)
//{
//	
//}
//
//void RTE::DirectX11DeviceResources::UpdateColorSpace()
//{
//	// *ppAdapter = nullptr;
//
//    ComPtr<IDXGIAdapter1> adapter;
//
//#if defined(__dxgi1_6_h__) && defined(NTDDI_WIN10_RS4)
//    ComPtr<IDXGIFactory6> factory6;
//    HRESULT hr = m_dxgiFactory.As(&factory6);
//    if (SUCCEEDED(hr))
//    {
//        for (UINT adapterIndex = 0;
//            SUCCEEDED(factory6->EnumAdapterByGpuPreference(
//                adapterIndex,
//                DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
//                IID_PPV_ARGS(adapter.ReleaseAndGetAddressOf())));
//            adapterIndex++)
//        {
//            DXGI_ADAPTER_DESC1 desc;
//            ThrowIfFailed(adapter->GetDesc1(&desc));
//
//            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
//            {
//                // Don't select the Basic Render Driver adapter.
//                continue;
//            }
//
//        #ifdef _DEBUG
//            wchar_t buff[256] = {};
//            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
//            OutputDebugStringW(buff);
//        #endif
//
//            break;
//        }
//    }
//#endif
//    if (!adapter)
//    {
//        for (UINT adapterIndex = 0;
//            SUCCEEDED(m_dxgiFactory->EnumAdapters1(
//                adapterIndex,
//                adapter.ReleaseAndGetAddressOf()));
//            adapterIndex++)
//        {
//            DXGI_ADAPTER_DESC1 desc;
//            ThrowIfFailed(adapter->GetDesc1(&desc));
//
//            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
//            {
//                // Don't select the Basic Render Driver adapter.
//                continue;
//            }
//
//#ifdef _DEBUG
//            wchar_t buff[256] = {};
//            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
//            OutputDebugStringW(buff);
//#endif
//
//            break;
//        }
//    }
//
//    *ppAdapter = adapter.Detach();
//}
