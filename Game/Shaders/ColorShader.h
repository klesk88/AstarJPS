#pragma once

#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Engine/Shaders/ShaderBase.h"

//directx
#include <d3d11.h>

class CColorShader final : public CShaderBase
{
public:
	CColorShader() = default;
	~CColorShader() = default;

	//CShaderBase
	void Init(ID3D11Device& rDevice, HWND hwnd) override;
	//CShaderBase

private:
	//CShaderBase
	void SetBufferData(const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjectionMatrix, D3D11_MAPPED_SUBRESOURCE& rOutMappedData) const override;
	//CShaderBase

	void InitializeShader(ID3D11Device*, HWND, LPCSTR, LPCSTR);
};
