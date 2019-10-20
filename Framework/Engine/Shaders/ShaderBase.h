#pragma once

#include <d3d11.h>
#include <d3dx11async.h>
#include <fstream>

#include "../Core/SimpleMath.h"
#include "../../Utils/ClassMacros.h"

class CShaderBase
{
	NON_COPYABLE_CLASS(CShaderBase)

public:
	CShaderBase();
	virtual ~CShaderBase();

	virtual bool Init(ID3D11Device& rDevice, HWND hwnd) = 0;
	void Shutdown();
	bool Render(const int indexCount, const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjectionMatrix, ID3D11DeviceContext& rDeviceContext) const;
	bool IsStilLValid() const { return m_pVertexShader != nullptr; }
protected:
	void OutputShaderErrorMessage(ID3D10Blob& rErrorMessage, HWND hwnd, LPCSTR shaderFilename);
	virtual void SetBufferData(const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjectionMatrix, D3D11_MAPPED_SUBRESOURCE& rOutMappedData) const = 0;

private:
	bool SetShaderParameters(DirectX::SimpleMath::Matrix worldMatrix, DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix, ID3D11DeviceContext& rDeviceContext) const;
	void RenderShader(ID3D11DeviceContext& rDeviceContext, const int indexCount) const;

protected:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pLayout;
	ID3D11Buffer* m_pMatrixBuffer;
};
