#pragma once

#include <d3d11.h>

#include "../../Framework/Engine/Core/SimpleMath.h"
#include "../../Framework/Engine/Shaders/ShaderBase.h"

class CColorShader final : public CShaderBase
{
public:
	CColorShader();
	~CColorShader();

	bool Init(ID3D11Device& rDevice, HWND hwnd) override;

private:
	bool InitializeShader(ID3D11Device*, HWND, LPCSTR, LPCSTR);
	void SetBufferData(const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjectionMatrix, D3D11_MAPPED_SUBRESOURCE& rOutMappedData) const override;
};
