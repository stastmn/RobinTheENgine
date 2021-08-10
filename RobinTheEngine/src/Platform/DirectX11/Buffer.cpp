#pragma once
#include "rtepch.h"
#include "Buffer.h"
#include "DirectX11RenderSystem.h"
#include "RobinTheEngine/Application.h"

RTE::Buffer::Buffer(char* data, int elementSize, int elementCount)
{
	DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*>(Application::Get().GetRenderSystem());

	this->bufferSize = elementCount * elementSize;
	this->stride = std::make_unique<UINT>(elementSize);

	D3D11_BUFFER_DESC desk;
	ZeroMemory(&desk, sizeof(desk));

	desk.Usage = D3D11_USAGE_DEFAULT;
	desk.ByteWidth = elementSize * elementCount;
	desk.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desk.CPUAccessFlags = 0;
	desk.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA bufferData;
	ZeroMemory(&bufferData, sizeof(bufferData));
	bufferData.pSysMem = data;

	ThrowIfFailed(rs->GetDevice()->CreateBuffer(&desk, &bufferData, buffer.GetAddressOf()));

}

RTE::Buffer::~Buffer()
{
	buffer->Release();
}

RTE::IndexBuffer::IndexBuffer(DWORD* data, int arraySize)
{
	DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*>(Application::Get().GetRenderSystem());

	elementCount = arraySize;
	
	D3D11_BUFFER_DESC desk;
	ZeroMemory(&desk, sizeof(desk));

	desk.Usage = D3D11_USAGE_DEFAULT;
	desk.ByteWidth = sizeof(DWORD) * elementCount;
	desk.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desk.CPUAccessFlags = 0;
	desk.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA bufferData;
	ZeroMemory(&bufferData, sizeof(bufferData));
	bufferData.pSysMem = data;

	ThrowIfFailed(rs->GetDevice()->CreateBuffer(&desk, &bufferData, buffer.GetAddressOf()));

}

RTE::IndexBuffer::~IndexBuffer()
{
	buffer->Release();
}
