#pragma once
#include <DirectXMath.h>

namespace RTE {


	struct vertex_POS_COLLOR {
		//TODO: should we use XMVECTOR instead of XMFLOAT's ?
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 collor;
		vertex_POS_COLLOR(float p1, float p2, float p3, float c1, float c2, float c3, float c4) :pos(p1, p2, p3), collor(c1, c2, c3, c4) {}
		

	};


}
