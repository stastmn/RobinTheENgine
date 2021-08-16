#include "rtepch.h"
#include "DirectX11RenderSystem.h"
#include "DirectXColors.h"
#include "RobinTheEngine/Core.h"
#include "dxgi1_2.h"


RTE::DirectX11RenderSystem::DirectX11RenderSystem(HWND hwnd) :m_hMainWnd(hwnd)
{
}

RTE::DirectX11RenderSystem::~DirectX11RenderSystem()
{
	//FlushCommandQueue();
}

void RTE::DirectX11RenderSystem::Init()
{
	//	//Create device
	//#if defined(DEBUG) || defined(_DEBUG) 
	//	// Enable the D3D12 debug layer.
	//	{
	//		ComPtr<ID3D12Debug> debugController;
	//		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
	//		debugController->EnableDebugLayer();
	//	}
	//#endif
	//

	ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&m_dxgiFactory)));


	LogAdapters();


	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_ClientWidth;
	sd.BufferDesc.Height = m_ClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = m_BackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = m_hMainWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	UINT flags = 0;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

	HRESULT hr = D3D11CreateDeviceAndSwapChain(adapterList[0],
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,//software driver type
		flags,//flags%
		NULL,//feature levels array
		0, //Feature levels count
		D3D11_SDK_VERSION,
		&sd,
		this->mSwapChain.GetAddressOf(),
		this->m_d3dDevice.GetAddressOf(),
		NULL,//suported feature level
		this->m_DeviceContext.GetAddressOf()
	);
	ThrowIfFailed(hr);
	//TODO: Create software adapter if faled

	//
	// Try to create hardware device.
	//HRESULT hardwareResult = D3D11CreateDevice(
	//	nullptr,             // default adapter
	//	D3D_FEATURE_LEVEL_11_0,
	//	IID_PPV_ARGS(&m_d3dDevice));

	//if (FAILED(hardwareResult))
	//{
	//	ComPtr<IDXGIAdapter> pWarpAdapter;
	//	ThrowIfFailed(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));
	//	//m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));


	//	ThrowIfFailed(D3D12CreateDevice(
	//		pWarpAdapter.Get(),
	//		D3D_FEATURE_LEVEL_11_0,
	//		IID_PPV_ARGS(&m_d3dDevice)));

	//	//D3D12CreateDevice(pWarpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice));
	//}
	//
	//	ThrowIfFailed(m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence)));
	//	//m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence));
	//
	//	m_RtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//	m_DsvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	//	m_CbvSrvUavDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//
	//
	//	// Check 4X MSAA quality support for our back buffer format.
	//	// All Direct3D 11 capable devices support 4X MSAA for all render 
	//	// target formats, so we only need to check quality support.
	//	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS QualityLevels;
	//	QualityLevels.Format = m_BackBufferFormat;
	//	QualityLevels.SampleCount = 4;
	//	QualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	//	QualityLevels.NumQualityLevels = 0;
	//	ThrowIfFailed(m_d3dDevice->CheckFeatureSupport(
	//		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
	//		&QualityLevels,
	//		sizeof(QualityLevels)));
	//
	//	//m_d3dDevice->CheckFeatureSupport(
	//	//	D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
	//	//	&QualityLevels,
	//	//	sizeof(QualityLevels));
	//
	//
	//	m_4xMsaaQuality = QualityLevels.NumQualityLevels;
	//	assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level.");




	//CreateSwapChain();


	OnResize(m_ClientWidth, m_ClientHeight);

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	ThrowIfFailed( m_d3dDevice->CreateRasterizerState(&rasterizerDesc, m_RasterizerState.GetAddressOf()));
	m_DeviceContext->RSSetState(m_RasterizerState.Get());

	D3D11_DEPTH_STENCIL_DESC depthStateDesc;
	ZeroMemory(&depthStateDesc, sizeof(depthStateDesc));

	depthStateDesc.DepthEnable = true;
	depthStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

	ThrowIfFailed( m_d3dDevice->CreateDepthStencilState(&depthStateDesc, m_DepthStencilState.GetAddressOf()));

}

void RTE::DirectX11RenderSystem::OnResize(int width, int height)
{
	m_ClientWidth = width;
	m_ClientHeight = height;

	RTE_ASSERT(m_d3dDevice, "Bad device!");
	RTE_ASSERT(mSwapChain, "Bad swapchain!");
	//
//	FlushCommandQueue();
//
//	ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc.Get(), nullptr));

	// Release the previous resources we will be recreating.
	for (int i = 0; i < SwapChainBufferCount; ++i)
		m_SwapChainBuffer[i].Reset();
	m_DepthStencilView.Reset();

	m_RenderTargetView.Reset();
	m_DepthStencilView.Reset();
	// Resize the swap chain.
	ThrowIfFailed(mSwapChain->ResizeBuffers(
		SwapChainBufferCount,
		m_ClientWidth, m_ClientHeight,
		m_BackBufferFormat,
		0));

	ComPtr<ID3D11Texture2D> backbuffer;
		ThrowIfFailed(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backbuffer.GetAddressOf())));
		ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backbuffer.Get(), NULL, m_RenderTargetView.GetAddressOf()));

	




		mCurrBackBuffer = 0;
	//
	//	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_RtvHeap->GetCPUDescriptorHandleForHeapStart());
	//	for (UINT i = 0; i < SwapChainBufferCount; i++)
	//	{
	//		ThrowIfFailed(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_SwapChainBuffer[i])));
	//		m_d3dDevice->CreateRenderTargetView(m_SwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
	//		rtvHeapHandle.Offset(1, m_RtvDescriptorSize);
	//	}
	//
		// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = m_ClientWidth;
	depthStencilDesc.Height = m_ClientHeight;
	depthStencilDesc.MipLevels = 1; 
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilBuffer;
	ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, DepthStencilBuffer.GetAddressOf()));
	ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(DepthStencilBuffer.Get(), 0, m_DepthStencilView.GetAddressOf()));


		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	//
	//	D3D12_CLEAR_VALUE optClear;
	//	optClear.Format = m_DepthStencilFormat;
	//	optClear.DepthStencil.Depth = 1.0f;
	//	optClear.DepthStencil.Stencil = 0;
	//	ThrowIfFailed(m_d3dDevice->CreateCommittedResource(
	//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
	//		D3D12_HEAP_FLAG_NONE,
	//		&depthStencilDesc,
	//		D3D12_RESOURCE_STATE_COMMON,
	//		&optClear,
	//		IID_PPV_ARGS(m_DepthStencilBuffer.GetAddressOf())));
	//
	//	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	//	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	//	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	//	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//	dsvDesc.Format = m_DepthStencilFormat;
	//	dsvDesc.Texture2D.MipSlice = 0;
	//	m_d3dDevice->CreateDepthStencilView(m_DepthStencilBuffer.Get(), &dsvDesc, DepthStencilView());
	//
	//	// Transition the resource from its initial state to be used as a depth buffer.
	//	m_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_DepthStencilBuffer.Get(),
	//		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
	//
	//	// Execute the resize commands.
	//	ThrowIfFailed(m_CommandList->Close());
	//	ID3D12CommandList* cmdsLists[] = { m_CommandList.Get() };
	//	m_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	//
	//	// Wait until resize is complete.
	//	FlushCommandQueue();
	
		// Update the viewport transform to cover the client area.
		m_ScreenViewport.TopLeftX = 0;
		m_ScreenViewport.TopLeftY = 0;
		m_ScreenViewport.Width = static_cast<float>(m_ClientWidth);
		m_ScreenViewport.Height = static_cast<float>(m_ClientHeight);
		m_ScreenViewport.MinDepth = 0.0f;
		m_ScreenViewport.MaxDepth = 1.0f;

		m_DeviceContext->RSSetViewports(1, &m_ScreenViewport);
	
		
		m_ScissorRect = { 0, 0, m_ClientWidth, m_ClientHeight };
		m_DeviceContext->RSSetScissorRects(1, &m_ScissorRect);

}

void RTE::DirectX11RenderSystem::OnRenderBegin()
{

	//	// Clear the back buffer and depth buffer.
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), DirectX::Colors::Magenta);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);

	m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 0);
}

void RTE::DirectX11RenderSystem::OnRenderEnd()
{

	//	// swap the back and front buffers
	ThrowIfFailed( mSwapChain->Present(0, 0));


}

void RTE::DirectX11RenderSystem::LogAdapterOutputs(IDXGIAdapter * adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring tmp = desc.DeviceName;
		std::string tmp2(tmp.begin(), tmp.end());
		std::string text = "***Output: ";
		text += std::string(tmp.begin(), tmp.end());
		RTE_CORE_INFO(text);

		LogOutputDisplayModes(output, m_BackBufferFormat);

		ReleaseCom(output);

		++i;
	}
}

void RTE::DirectX11RenderSystem::LogAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	adapterList;
	while (m_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{

		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		std::wstring tmp = desc.Description;
		std::string text = " * **Adapter: ";
		text += std::string(tmp.begin(), tmp.end());
		RTE_CORE_INFO(text);
		adapterList.push_back(adapter);    ++i;
	}
#ifdef DEBUG
	for (size_t i = 0; i < adapterList.size(); ++i) {

		LogAdapterOutputs(adapterList[i]);
		//ReleaseCom(adapterList[i]);
	}
	#endif // DEBUG
}


void RTE::DirectX11RenderSystem::LogOutputDisplayModes(IDXGIOutput * output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::string text =
			"Width = " + std::to_string(x.Width) + " " +
			"Height = " + std::to_string(x.Height) + " " +
			"Refresh = " + std::to_string(n) + "/" + std::to_string(d);

		RTE_CORE_INFO(text);
	}
}

//void RTE::DirectX11RenderSystem::CreateSwapChain()
//{
//	// Release the previous swapchain we will be recreating.
//	mSwapChain.Reset();
//
//	DXGI_SWAP_CHAIN_DESC sd;
//	sd.BufferDesc.Width = m_ClientWidth;
//	sd.BufferDesc.Height = m_ClientHeight;
//	sd.BufferDesc.RefreshRate.Numerator = 60;
//	sd.BufferDesc.RefreshRate.Denominator = 1;
//	sd.BufferDesc.Format = m_BackBufferFormat;
//	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//	sd.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
//	sd.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.BufferCount = SwapChainBufferCount;
//	sd.OutputWindow = m_hMainWnd;
//	sd.Windowed = true;
//	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//
//	IDXGIFactory2* dxgiFactory2 = 0;
//	HRESULT hr = m_dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
//	if (SUCCEEDED(hr))
//	{
//		// This system has DirectX 11.1 or later installed, so we can use this interface
//		IDXGIDevice * dxgiDevice = 0;
//		HRESULT hr = m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)& dxgiDevice);
//		RTE_ASSERT(hr, "Bad cast to dxgidevice");
//
//			//dxgiFactory2->CreateSwapChainForHwnd(dxgiDevice,m_hMainWnd,&sd,);
//		dxgiFactory2->Release();
//	}
//
//	// Note: Swap chain uses queue to perform flush.
//	hr = m_dxgiFactory->CreateSwapChain(
//		adapterList[0],
//		&sd,
//		mSwapChain.GetAddressOf());
//	ThrowIfFailed(hr);
//
//}

//D3D12_CPU_DESCRIPTOR_HANDLE RTE::DirectX11RenderSystem::CurrentBackBufferView() const
//{
//	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		m_RtvHeap->GetCPUDescriptorHandleForHeapStart(),
//		mCurrBackBuffer,
//		m_RtvDescriptorSize);
//
//}
//
//D3D12_CPU_DESCRIPTOR_HANDLE RTE::DirectX11RenderSystem::DepthStencilView() const
//{
//	return m_DsvHeap->GetCPUDescriptorHandleForHeapStart();
//
//}
//
//ID3D12Resource* RTE::DirectX11RenderSystem::CurrentBackBuffer() const
//{
//	return m_SwapChainBuffer[mCurrBackBuffer].Get();
//
//}
//
//void RTE::DirectX11RenderSystem::FlushCommandQueue()
//{
//	// Advance the fence value to mark commands up to this fence point.
//	m_CurrentFence++;
//
//	// Add an instruction to the command queue to set a new fence point.  Because we 
//	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
//	// processing all the commands prior to this Signal().
//	ThrowIfFailed(m_CommandQueue->Signal(m_Fence.Get(), m_CurrentFence));
//
//	// Wait until the GPU has completed commands up to this fence point.
//	if (m_Fence->GetCompletedValue() < m_CurrentFence)
//	{
//		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
//
//		// Fire event when GPU hits current fence.  
//		ThrowIfFailed(m_Fence->SetEventOnCompletion(m_CurrentFence, eventHandle));
//
//		// Wait until the GPU hits current fence event is fired.
//		WaitForSingleObject(eventHandle, INFINITE);
//		CloseHandle(eventHandle);
//	}
//
//}
//
