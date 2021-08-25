#pragma once
#include <DirectXMath.h>

namespace RTE {


	struct vertex_POS_COLLOR {
		//TODO: should we use XMVECTOR instead of XMFLOAT's ?
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 collor;
		vertex_POS_COLLOR(float p1, float p2, float p3, float c1, float c2, float c3, float c4) :pos(p1, p2, p3), collor(c1, c2, c3, c4) {}
		vertex_POS_COLLOR() {};

	};

	struct vertex_Gouraud_shading {
		//TODO: should we use XMVECTOR instead of XMFLOAT's ?

		DirectX::XMFLOAT2 texCoord;
		DirectX::XMFLOAT2 normalCoord;
		DirectX::XMFLOAT3 pos;


	};


}






	/*
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
	
	
	
	*/
