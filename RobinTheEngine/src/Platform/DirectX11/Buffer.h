#pragma once
#include "d3d11.h"
#include <wrl.h>

namespace RTE {

	template<class T>
	class vertexBuffer {

	public:
		vertexBuffer(T* data, int numOfElements) {
			DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*>(Application::Get().GetRenderSystem());

			this->bufferSize = numOfElements * sizeof(T);
				this->stride = std::make_unique<UINT>(sizeof(T));

			D3D11_BUFFER_DESC desk;
			ZeroMemory(&desk, sizeof(desk));

			desk.Usage = D3D11_USAGE_DEFAULT;
			desk.ByteWidth = sizeof(T) * numOfElements;
			desk.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desk.CPUAccessFlags = 0;
			desk.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA bufferData;
			ZeroMemory(&bufferData, sizeof(bufferData));
			bufferData.pSysMem = data;

			ThrowIfFailed(rs->GetDevice()->CreateBuffer(&desk, &bufferData, buffer.GetAddressOf()));
		}
		~vertexBuffer() {};

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		std::unique_ptr<UINT> stride;
		UINT bufferSize;

		vertexBuffer(vertexBuffer& rhs) = delete;
		vertexBuffer(vertexBuffer&& rhs) = delete;
		vertexBuffer& operator=(vertexBuffer& rhs) = delete;
		vertexBuffer& operator=(vertexBuffer&& rhs) = delete;

	public:
		ID3D11Buffer* Get() { return buffer.Get(); }
		ID3D11Buffer* const* GetAdressOf() { return buffer.GetAddressOf(); }
		UINT BufferSize() { return bufferSize; }
		UINT * StridePtr() { return stride.get(); }

	};

	class IndexBuffer {
	public:
		IndexBuffer(DWORD* data, int arraySize);
		~IndexBuffer();


	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		UINT elementCount;

		IndexBuffer(IndexBuffer& rhs) = delete;
		IndexBuffer(IndexBuffer&& rhs) = delete;
		IndexBuffer& operator=(IndexBuffer& rhs) = delete;
		IndexBuffer& operator=(IndexBuffer&& rhs) = delete;

	public:
		ID3D11Buffer* Get() { return buffer.Get(); }
		ID3D11Buffer* const* GetAdressOf() { return buffer.GetAddressOf(); }
		UINT ElementCount() { return elementCount; }

	};
}
