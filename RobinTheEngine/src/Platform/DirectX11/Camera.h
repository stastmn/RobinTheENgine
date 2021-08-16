#pragma once
#include <DirectXMath.h>
using namespace DirectX;



namespace RTE {

	class Camera {

	public:
		Camera();
		void SetProjectionProperties(float fovDegrees, float aspectRatio, float nearZ, float farZ);

		const XMMATRIX& GetViewMatrix();
		const XMMATRIX& GetProjectionMatrix();

		const XMVECTOR& GetPositionVec();
		const XMVECTOR& GetRotationVec();
		const XMFLOAT3& GetPositionFloat3();
		const XMFLOAT3& GetRotationFloat3();

		void SetPosition(const XMVECTOR& vec);
		void SetPosition(const XMFLOAT3& vec);
		void AdjustPosition(const XMVECTOR& vec);
		void AdjustPosition(const XMFLOAT3& vec);
		void SetRotation(const XMVECTOR& vec);
		void SetRotation(const XMFLOAT3& vec);
		void AdjustRotation(const XMVECTOR& vec);
		void AdjustRotation(const XMFLOAT3& vec);

	private:
		void UpdateViewMatrix();
		XMVECTOR m_posVec;
		XMVECTOR m_rotVec;
		XMFLOAT3 m_pos;
		XMFLOAT3 m_rot;
		XMMATRIX m_viewMatrix;
		XMMATRIX m_projectionMatrix;


		const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0, 0, 1, 0);
		const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0, 1, 0, 0);


	};






}
