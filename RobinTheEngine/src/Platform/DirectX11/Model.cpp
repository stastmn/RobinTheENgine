#include "rtepch.h"
#include "Model.h"
#include "RobinTheEngine/d3dUtils.h"
#include "Platform/DirectX11/DirectX11RenderSystem.h"
#include "RobinTheEngine/Application.h"

using namespace D3DUtils;

bool RTE::Model::Initialize(const std::string& path, ConstantBuffer<CB_VS_MATRIX4x4>& cb_vs_vertexshader)
{
	DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*> (Application::Get().GetRenderSystem());

	this->device = rs->GetDevice().Get();
	this->deviceContext = rs->GetContext().Get();
	this->cb_vs_vertexshader = &cb_vs_vertexshader;


	if (!this->LoadModel(path))
		return false;



	SetPosition(0.0f, 0.0f, 0.0f);
	SetRotation(0.0f, 0.0f, 0.0f);
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

	// draw submeshes
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
}


bool RTE::Model::LoadModel(const std::string & filePath)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filePath,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded);

	if (pScene == NULL)
		return false;


	this->ProcessNode(pScene->mRootNode, pScene);
	return true;
}

void RTE::Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->ProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

RTE::Mesh RTE::Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	std::vector<vertex_Gouraud_shading> vertices;
	std::vector<DWORD> indices;

	//Get vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		vertex_Gouraud_shading vertex;

		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		//if ( mesh->mNormals[0] ) {
		//	vertex.normalCoord.x = (float)mesh->mNormals[i].x;
		//	vertex.normalCoord.y = (float)mesh->mNormals[i].y;

		//}

		vertices.push_back(vertex);
	}

	//Get indices
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh( vertices, indices);
}

void RTE::Model::UpdateWorldMatrix()
{
	this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}



const XMVECTOR & RTE::Model::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3 & RTE::Model::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR & RTE::Model::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3 & RTE::Model::GetRotationFloat3() const
{
	return this->rot;
}

void RTE::Model::SetPosition(const XMVECTOR & pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateWorldMatrix();
}

void RTE::Model::SetPosition(const XMFLOAT3 & pos)
{
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void RTE::Model::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void RTE::Model::AdjustPosition(const XMVECTOR & pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateWorldMatrix();
}

void RTE::Model::AdjustPosition(const XMFLOAT3 & pos)
{
	this->pos.x += pos.y;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void RTE::Model::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void RTE::Model::SetRotation(const XMVECTOR & rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateWorldMatrix();
}

void RTE::Model::SetRotation(const XMFLOAT3 & rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void RTE::Model::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void RTE::Model::AdjustRotation(const XMVECTOR & rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateWorldMatrix();
}

void RTE::Model::AdjustRotation(const XMFLOAT3 & rot)
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void RTE::Model::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void RTE::Model::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
		return;

	lookAtPos.x = this->pos.x - lookAtPos.x;
	lookAtPos.y = this->pos.y - lookAtPos.y;
	lookAtPos.z = this->pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

const XMVECTOR & RTE::Model::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR & RTE::Model::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR & RTE::Model::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR & RTE::Model::GetLeftVector()
{
	return this->vec_left;
}
