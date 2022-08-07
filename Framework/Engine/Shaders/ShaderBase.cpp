#include "Framework/Engine/Shaders/ShaderBase.h"

using namespace DirectX::SimpleMath;

CShaderBase::~CShaderBase()
{
	Shutdown();
}

void CShaderBase::Shutdown()
{
	if (m_pMatrixBuffer)
	{
		m_pMatrixBuffer->Release();
		m_pMatrixBuffer = nullptr;
	}

	if (m_pLayout)
	{
		m_pLayout->Release();
		m_pLayout = nullptr;
	}

	if (m_pPixelShader)
	{
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	if (m_pVertexShader)
	{
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}
}

void CShaderBase::Render(const int indexCount, const Matrix& rWorldMatrix, const Matrix& rViewMatrix, const Matrix& rProjectionMatrix, ID3D11DeviceContext& rDeviceContext) const
{
	// Set the shader parameters that it will use for rendering.
	const bool bResult = SetShaderParameters(rWorldMatrix, rViewMatrix, rProjectionMatrix, rDeviceContext);
	if (!bResult)
	{
		return;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(rDeviceContext, indexCount);
}

void CShaderBase::OutputShaderErrorMessage(ID3D10Blob& rErrorMessage, HWND hwnd, LPCSTR shaderFilename)
{
	std::ofstream fout;

	const char* compileErrors = (char*)(rErrorMessage.GetBufferPointer());
	const size_t bufferSize = rErrorMessage.GetBufferSize();

	fout.open("shader-error.txt");

	for (int i = 0; i < static_cast<int>(bufferSize); i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	rErrorMessage.Release();
	MessageBox(hwnd, "Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);
}

bool CShaderBase::SetShaderParameters(Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix, ID3D11DeviceContext& rDeviceContext) const
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int uBufferNumber;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = rDeviceContext.Map(m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	SetBufferData(worldMatrix, viewMatrix, projectionMatrix, mappedResource);

	// Unlock the constant buffer.
	rDeviceContext.Unmap(m_pMatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	uBufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	rDeviceContext.VSSetConstantBuffers(uBufferNumber, 1, &m_pMatrixBuffer);

	return true;
}

void CShaderBase::RenderShader(ID3D11DeviceContext& rDeviceContext, const int indexCount) const
{
	rDeviceContext.IASetInputLayout(m_pLayout);

	rDeviceContext.VSSetShader(m_pVertexShader, nullptr, 0);
	rDeviceContext.PSSetShader(m_pPixelShader, nullptr, 0);

	rDeviceContext.DrawIndexed(indexCount, 0, 0);
}