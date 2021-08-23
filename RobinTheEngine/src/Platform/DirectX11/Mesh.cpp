#include "rtepch.h"
#include "Mesh.h"
#include "Platform/DirectX11/DirectX11RenderSystem.h"
#include "RobinTheEngine/Application.h"


//RTE::Mesh::Mesh(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::vector<vertex_Gouraud_shading>& vertices, std::vector<DWORD>& indices)
//	: vertexbuffer(vertices.data(),vertices.size()), indexbuffer(indices.data(),indices.size())
//{
//	DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*>(Application::Get().GetRenderSystem());
//
//	this->deviceContext = rs->GetContext().Get();
//}
//
//RTE::Mesh::Mesh(const Mesh & mesh)
//{
//	this->deviceContext = mesh.deviceContext;
//	//this->indexbuffer = mesh.indexbuffer;
//	//this->vertexbuffer = mesh.vertexbuffer;
//}
//
//void RTE::Mesh::Draw()
//{
//	UINT offset = 0;
//	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexbuffer.GetAddressOf(), this->vertexbuffer.StridePtr(), &offset);
//	this->deviceContext->IASetIndexBuffer(this->indexbuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
//	this->deviceContext->DrawIndexed(this->indexbuffer.ElementCount(), 0, 0);
//}
