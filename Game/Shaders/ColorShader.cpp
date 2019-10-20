#include "ColorShader.h"

#include "ColorDataStructure.h"

using namespace DirectX::SimpleMath;

CColorShader::CColorShader()
{}

CColorShader::~CColorShader()
{}

bool CColorShader::Init(ID3D11Device& rDevice, HWND hwnd)
{
	if (m_pVertexShader)
	{
		return true;
	}

	// Initialize the vertex and pixel shaders.
	return InitializeShader(&rDevice, hwnd, "Shaders/color.vs", "Shaders/color.ps");
}

bool CColorShader::InitializeShader(ID3D11Device* device, HWND hwnd, LPCSTR vsFilename, LPCSTR psFilename)
{
	HRESULT result;
	ID3D10Blob* pErroeMessage = nullptr;
	ID3D10Blob* pVertexShaderBuffer = nullptr;
	ID3D10Blob* pPixelShaderBuffer = nullptr;

	result = D3DX11CompileFromFile(vsFilename,
		nullptr,
		nullptr,
		"ColorVertexShader",
		"vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&pVertexShaderBuffer,
		&pErroeMessage,
		nullptr);

	if (FAILED(result))
	{
		if (pErroeMessage)
		{
			OutputShaderErrorMessage(*pErroeMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, vsFilename, "Missing Shader File", MB_OK);
		}

		return false;
	}

	result = D3DX11CompileFromFile(
		psFilename,
		nullptr,
		nullptr,
		"ColorPixelShader",
		"ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&pPixelShaderBuffer,
		&pErroeMessage,
		nullptr);

	if (FAILED(result))
	{
		if (pErroeMessage)
		{
			OutputShaderErrorMessage(*pErroeMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, psFilename, "Missing Shader File", MB_OK);
		}

		return false;
	}

	result = device->CreateVertexShader(pVertexShaderBuffer->GetBufferPointer(), pVertexShaderBuffer->GetBufferSize(), nullptr, &m_pVertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(), pPixelShaderBuffer->GetBufferSize(), nullptr, &m_pPixelShader);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	const unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(
		polygonLayout,
		numElements,
		pVertexShaderBuffer->GetBufferPointer(),
		pVertexShaderBuffer->GetBufferSize(),
		&m_pLayout);

	if (FAILED(result))
	{
		return false;
	}

	pVertexShaderBuffer->Release();
	pPixelShaderBuffer->Release();

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(ColorShaderDataStructures::sMatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, nullptr, &m_pMatrixBuffer);
	return SUCCEEDED(result);
}

void CColorShader::SetBufferData(const Matrix& rWorldMatrix, const Matrix& rViewMatrix, const Matrix& rProjectionMatrix, D3D11_MAPPED_SUBRESOURCE& rOutMappedData) const
{
	ColorShaderDataStructures::sMatrixBufferType* pMatrixBuffer = static_cast<ColorShaderDataStructures::sMatrixBufferType*>(rOutMappedData.pData);

	// Copy the matrices into the constant buffer.
	pMatrixBuffer->world = rWorldMatrix;
	pMatrixBuffer->view = rViewMatrix;
	pMatrixBuffer->projection = rProjectionMatrix;
}
