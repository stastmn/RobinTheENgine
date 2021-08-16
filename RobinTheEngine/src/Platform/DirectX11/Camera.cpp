#include "rtepch.h"
#include "Camera.h"

RTE::Camera::Camera()
{
	m_pos = XMFLOAT3(0.f, 0.f, 0.f);
	m_posVec = XMLoadFloat3(&m_pos);
	m_rot = XMFLOAT3(0.f, 0.f, 0.f);
	m_rotVec = XMLoadFloat3(&m_rot);
	UpdateViewMatrix();
}

void RTE::Camera::SetProjectionProperties(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	//Convert degrees to radians
	float fov = (fovDegrees / 360) * XM_PI;

	m_projectionMatrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);

}

const XMMATRIX & RTE::Camera::GetViewMatrix()
{
	return this->m_viewMatrix;
}

const XMMATRIX & RTE::Camera::GetProjectionMatrix()
{
	return this->m_projectionMatrix;
}

const XMVECTOR & RTE::Camera::GetPositionVec()
{
	return this->m_posVec;
}

const XMVECTOR & RTE::Camera::GetRotationVec()
{
	return this->m_rotVec;
}

const XMFLOAT3 & RTE::Camera::GetPositionFloat3()
{
	return m_pos;
}

const XMFLOAT3 & RTE::Camera::GetRotationFloat3()
{
	return m_rot;
}

void RTE::Camera::SetPosition(const XMVECTOR & vec)
{
	XMStoreFloat3(&m_pos, vec);
	m_posVec = vec;
	UpdateViewMatrix();
}

void RTE::Camera::SetPosition(const XMFLOAT3 & vec)
{
	m_pos = vec;
	m_posVec = XMLoadFloat3(&m_pos);
	UpdateViewMatrix();
}

void RTE::Camera::AdjustPosition(const XMVECTOR & vec)
{
	m_posVec += vec;
	XMStoreFloat3(&m_pos, m_posVec);
	UpdateViewMatrix();
}

void RTE::Camera::AdjustPosition(const XMFLOAT3 & vec)
{
	m_posVec += XMLoadFloat3(&vec);
	XMStoreFloat3(&m_pos, m_posVec);
	UpdateViewMatrix();
}

void RTE::Camera::SetRotation(const XMVECTOR & vec)
{
	m_rotVec = vec;
	XMStoreFloat3(&m_rot, m_rotVec);
	UpdateViewMatrix();
}

void RTE::Camera::SetRotation(const XMFLOAT3 & vec)
{
	m_rot = vec;
	m_rotVec = XMLoadFloat3(&m_rot);
	UpdateViewMatrix();
}

void RTE::Camera::AdjustRotation(const XMVECTOR & vec)
{
	m_rotVec += vec;
	XMStoreFloat3(&m_rot, m_rotVec);
	UpdateViewMatrix();
}

void RTE::Camera::AdjustRotation(const XMFLOAT3 & vec)
{
	m_rotVec += XMLoadFloat3(&vec);
	XMStoreFloat3(&m_rot, m_rotVec);
	UpdateViewMatrix();
}

void RTE::Camera::UpdateViewMatrix()
{
	XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(m_rotVec);
	XMVECTOR target = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rotation);
	target += m_posVec;
	XMVECTOR upDir = XMVector3TransformCoord(DEFAULT_UP_VECTOR, rotation);

	m_viewMatrix = XMMatrixLookAtLH(m_posVec, target, upDir);

}
