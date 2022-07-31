#pragma once

#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"

//external
#include <d3d11.h>
#include <d3dx11async.h>
#include <fstream>

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CShaderBase
{
	NON_COPYABLE_CLASS(CShaderBase)

public:
	CShaderBase() = default;
	virtual ~CShaderBase();

	virtual void Init(ID3D11Device& rDevice, HWND hwnd) = 0;
	void Shutdown();

	void Render(const int indexCount, const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjectionMatrix, ID3D11DeviceContext& rDeviceContext) const;
	[[nodiscard]] bool IsStilLValid() const { return m_pVertexShader != nullptr; }

protected:
	void OutputShaderErrorMessage(ID3D10Blob& rErrorMessage, HWND hwnd, LPCSTR shaderFilename);
	virtual void SetBufferData(const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjectionMatrix, D3D11_MAPPED_SUBRESOURCE& rOutMappedData) const = 0;

private:
	[[nodiscard]] bool SetShaderParameters(DirectX::SimpleMath::Matrix worldMatrix, DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix, ID3D11DeviceContext& rDeviceContext) const;
	[[nodiscard]] void RenderShader(ID3D11DeviceContext& rDeviceContext, const int indexCount) const;

protected:
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pLayout = nullptr;
	ID3D11Buffer* m_pMatrixBuffer = nullptr;
};
