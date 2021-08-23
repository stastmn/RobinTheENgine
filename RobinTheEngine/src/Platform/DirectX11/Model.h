#pragma once
#include "Platform/DirectX11/Buffer.h"
#include "Platform/DirectX11/Vertex.h"
#include "Platform/DirectX11/ConstantBuffer.h"

using namespace DirectX;

namespace RTE {


	class Model
	{
	public:
		bool Initialize(ConstantBuffer<CB_VS_MATRIX4x4>& cb_vs_vertexshader);
		void SetTexture(ID3D11ShaderResourceView * texture);
		void Draw(const XMMATRIX & viewProjectionMatrix);
	private:
		void UpdateWorldMatrix();

		ID3D11Device * device = nullptr;
		ID3D11DeviceContext * deviceContext = nullptr;
		ConstantBuffer<CB_VS_MATRIX4x4> * cb_vs_vertexshader = nullptr;
		ID3D11ShaderResourceView * texture = nullptr;

		vertexBuffer<vertex_POS_COLLOR> vertexBuffer;
		IndexBuffer indexBuffer;

		XMMATRIX worldMatrix = XMMatrixIdentity();
	};






}




