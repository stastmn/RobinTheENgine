#pragma once
#include "d3d11.h"
#include <wrl.h>

namespace RTE {


	class Buffer {

	public:
		Buffer(char* data, int elementSize, int arraySize);
		~Buffer();

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		std::unique_ptr<UINT> stride;
		UINT bufferSize;

		Buffer(Buffer& rhs) = delete;
		Buffer(Buffer&& rhs) = delete;
		Buffer& operator=(Buffer& rhs) = delete;
		Buffer& operator=(Buffer&& rhs) = delete;

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
