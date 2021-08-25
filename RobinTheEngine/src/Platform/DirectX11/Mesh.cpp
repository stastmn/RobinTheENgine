#include "rtepch.h"
#include "Mesh.h"
#include "Platform/DirectX11/DirectX11RenderSystem.h"
#include "RobinTheEngine/Application.h"
#include "RobinTheEngine/d3dUtils.h"



using namespace D3DUtils;

RTE::Mesh::Mesh( std::vector<vertex_Gouraud_shading>& vertices, std::vector<DWORD>& indices)
{
	RTE::DirectX11RenderSystem* rs = static_cast<RTE::DirectX11RenderSystem*>(RTE::Application::Get().GetRenderSystem());
		this->deviceContext = rs->GetContext().Get(); 

	ThrowIfFailed(vertexbuffer.Init(vertices.data(), vertices.size()));

	ThrowIfFailed(indexbuffer.Init( indices.data(), indices.size()));
	
}

RTE::Mesh::Mesh(const Mesh & mesh)
{
	this->deviceContext = mesh.deviceContext;
	this->indexbuffer = mesh.indexbuffer;
	this->vertexbuffer = mesh.vertexbuffer;
}

void RTE::Mesh::Draw()
{
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexbuffer.GetAddressOf(), this->vertexbuffer.StridePtr(), &offset);
	this->deviceContext->IASetIndexBuffer(this->indexbuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	this->deviceContext->DrawIndexed(this->indexbuffer.ElementCount(), 0, 0);
}
