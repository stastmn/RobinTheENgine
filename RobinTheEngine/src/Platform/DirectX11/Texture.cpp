#include "rtepch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Platform/DirectX11/Texture.h"
#include "Platform/DirectX11/DirectX11RenderSystem.h"
#include "RobinTheEngine/Application.h"

#include "WICTextureLoader.h"
#pragma comment(lib,"DirectXTK.lib")

RTE::Texture::Texture(const std::string& filePath, aiTextureType type)
{
	this->type = type;

	int x, y, n;
	int result = stbi_info(filePath.c_str(), &x, &y, &n);
	if (result)
	{
		CreateTextureFromFile(filePath);

	}
	else
	{
		CreateTextureFromFile(DEFAULT_PATH_TO_ERROR_TEXTURE);
	}
	return;
}


aiTextureType RTE::Texture::GetType()
{
	return this->type;
}

ID3D11ShaderResourceView * RTE::Texture::GetTextureResourceView()
{
	return this->textureView.Get();
}

ID3D11ShaderResourceView ** RTE::Texture::GetTextureResourceViewAddress()
{
	return this->textureView.GetAddressOf();
}

void RTE::Texture::CreateTextureFromFile(const std::string & path)
{
	//int width, height, chanels;

	//unsigned char* data = stbi_load(path.c_str(), &width, &height, &chanels, 0);
	//if (data == NULL) {
	//	RTE_CORE_WARN(stbi_failure_reason());
	//	RTE_ASSERT(data, "Cannot load texture from file.");
	//}

	//DXGI_FORMAT format; //TODO: choose correct format using chanels count
	//CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_B8G8R8A8_UNORM, width, height);
	//ComPtr<ID3D11Texture2D>  p2DTexture;
	//D3D11_SUBRESOURCE_DATA initialData{};
	//initialData.pSysMem = (void*)data;
	//initialData.SysMemPitch = width * chanels;
	DirectX11RenderSystem* rs = static_cast<DirectX11RenderSystem*>(Application::Get().GetRenderSystem());
	////HRESULT res = rs->GetDevice()->CreateTexture2D(&textureDesc, &initialData, p2DTexture.GetAddressOf());
	std::wstring wpath(path.begin(), path.end());
	DirectX::CreateWICTextureFromFile(rs->GetDevice().Get(), wpath.c_str(),texture.GetAddressOf(), textureView.GetAddressOf());
	
	//ThrowIfFailed(res);
	
	//
	//texture = static_cast<ID3D11Texture2D*>(p2DTexture.Get());
	//CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);
	//ThrowIfFailed( rs->GetDevice()->CreateShaderResourceView(texture.Get(), &srvDesc, textureView.GetAddressOf()));
}



