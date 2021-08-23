#include "rtepch.h"
#include "Model.h"
#include "RobinTheEngine/d3dUtils.h"
#include "Platform/DirectX11/DirectX11RenderSystem.h"
#include "RobinTheEngine/Application.h"

using namespace D3DUtils;

bool RTE::Model::Initialize(ConstantBuffer<CB_VS_MATRIX4x4>& cb_vs_vertexshader)
{
	DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*> (Application::Get().GetRenderSystem());

	this->device = rs->GetDevice().Get();
	this->deviceContext = rs->GetContext().Get();
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	//Textured Square
	vertex_POS_COLLOR  v[] =
	{
		vertex_POS_COLLOR(1.f, 1.f, 1.f,		0.0f ,1.0f, 0.0f, 0.0f), //[2]
		vertex_POS_COLLOR(-1.f, 1.f, -1.f,		0.0f, 1.0f, 0.0f, 0.0f), //[4] 1
		vertex_POS_COLLOR(1.f, 1.f, -1.f,		0.0f, 1.0f, 0.0f, 0.0f), //[0]

		vertex_POS_COLLOR(-1.f, -1.f, 1.f,		0.0f, 0.0f, 1.0f, 0.0f), //[7]
		vertex_POS_COLLOR(1.f, 1.f, 1.f,		0.0f ,0.0f, 1.0f, 0.0f), //[2] 2
		vertex_POS_COLLOR(1.f, -1.f, 1.f,		0.0f, 0.0f, 1.0f, 0.0f), //[3]

		vertex_POS_COLLOR(-1.f, -1.f, -1.f,		-1.0f, 0.0f, 0.0f, 0.0f), //[5]
		vertex_POS_COLLOR(-1.f, 1.f, 1.f,		-1.0f, 0.0f, 0.0f, 0.0f), //[6] 3
		vertex_POS_COLLOR(-1.f, -1.f, 1.f,		-1.0f, 0.0f, 0.0f, 0.0f), //[7]

		vertex_POS_COLLOR(-1.f, -1.f, 1.f,		0.0f, -1.0f, 0.0f, 0.0f), //[7]
		vertex_POS_COLLOR(1.f, -1.f, -1.f,		0.0f, -1.0f, 0.0f, 0.0f), //[1] 4
		vertex_POS_COLLOR(-1.f, -1.f, -1.f,		0.0f, -1.0f, 0.0f, 0.0f), //[5]

		vertex_POS_COLLOR(1.f, -1.f, 1.f,		1.0f, 0.0f, 0.0f, 0.0f), //[3]
		vertex_POS_COLLOR(1.f, 1.f, -1.f,		1.0f, 0.0f, 0.0f, 0.0f), //[0] 5
		vertex_POS_COLLOR(1.f, -1.f, -1.f,		1.0f, 0.0f, 0.0f, 0.0f), //[1]

		vertex_POS_COLLOR(1.f, -1.f, -1.f,		0.0f, 0.0f, -1.0f, 0.0f), //[1]
		vertex_POS_COLLOR(-1.f, 1.f, -1.f,		0.0f, 0.0f, -1.0f, 0.0f), //[4] 6
		vertex_POS_COLLOR(-1.f, -1.f, -1.f,		0.0f, 0.0f, -1.0f, 0.0f), //[5]

		vertex_POS_COLLOR(-1.f, 1.f, 1.f,		0.0f, 1.0f, 0.0f, 0.0f), //[6] 
		vertex_POS_COLLOR(-1.f, 1.f, -1.f,		0.0f, 1.0f, 0.0f, 0.0f), //[4] 1
		vertex_POS_COLLOR(1.f, 1.f, 1.f,		0.0f ,1.0f, 0.0f, 0.0f), //[2]

		vertex_POS_COLLOR(-1.f, 1.f, 1.f,		0.0f, 0.0f, 1.0f, 0.0f), //[6] 
		vertex_POS_COLLOR(1.f, 1.f, 1.f,		0.0f ,0.0f, 1.0f, 0.0f), //[2] 2
		vertex_POS_COLLOR(-1.f, -1.f, 1.f,		0.0f, 0.0f, 1.0f, 0.0f), //[7]

		vertex_POS_COLLOR(-1.f, 1.f, -1.f,		-1.0f, 0.0f, 0.0f, 0.0f), //[4] 
		vertex_POS_COLLOR(-1.f, 1.f, 1.f,		-1.0f, 0.0f, 0.0f, 0.0f), //[6] 3
		vertex_POS_COLLOR(-1.f, -1.f, -1.f,		-1.0f, 0.0f, 0.0f, 0.0f), //[5]

		vertex_POS_COLLOR(1.f, -1.f, 1.f,		0.0f, -1.0f, 0.0f, 0.0f), //[3]
		vertex_POS_COLLOR(1.f, -1.f, -1.f,		0.0f, -1.0f, 0.0f, 0.0f), //[1] 4
		vertex_POS_COLLOR(-1.f, -1.f, 1.f,		0.0f, -1.0f, 0.0f, 0.0f), //[7]

		vertex_POS_COLLOR(1.f, 1.f, 1.f,		1.0f ,0.0f, 0.0f, 0.0f), //[2] 
		vertex_POS_COLLOR(1.f, 1.f, -1.f,		1.0f, 0.0f, 0.0f, 0.0f), //[0] 5
		vertex_POS_COLLOR(1.f, -1.f, 1.f,		1.0f, 0.0f, 0.0f, 0.0f), //[3]

		vertex_POS_COLLOR(1.f, 1.f, -1.f,		0.0f, 0.0f, -1.0f, 0.0f), //[0]
		vertex_POS_COLLOR(-1.f, 1.f, -1.f,		0.0f, 0.0f, -1.0f, 0.0f), //[4] 6
		vertex_POS_COLLOR(1.f, -1.f, -1.f,		0.0f, 0.0f, -1.0f, 0.0f), //[1]

	};

	//Load Vertex Data
	ThrowIfFailed(vertexBuffer.Init(v, ARRAYSIZE(v)));

	DWORD indices[] =
	{
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35,

	};

	//Load Index Data
	ThrowIfFailed(indexBuffer.Init(indices, ARRAYSIZE(indices)));

	UpdateWorldMatrix();
	return true;
}

void RTE::Model::SetTexture(ID3D11ShaderResourceView * texture)
{
	this->texture = texture;
}

void RTE::Model::Draw(const XMMATRIX & viewProjectionMatrix)
{
	//Update Constant buffer with WVP Matrix
	XMStoreFloat4x4(&cb_vs_vertexshader->data.matrix, XMMatrixTranspose(this->worldMatrix * viewProjectionMatrix)); //Calculate World-View-Projection Matrix
	cb_vs_vertexshader->WriteBuffer();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer.ElementCount(), 0, 0); //Draw
}

void RTE::Model::UpdateWorldMatrix()
{
	this->worldMatrix = XMMatrixIdentity();
}
