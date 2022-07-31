#include "Game/Drawables/ColorDrawableBase.h"

#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Render/Renderer.h"

using namespace DirectX::SimpleMath;

CColorDrawableBase::CColorDrawableBase(const D3D_PRIMITIVE_TOPOLOGY primitiveTopology, const D3D11_USAGE bufferUsage/* = D3D11_USAGE::D3D11_USAGE_DEFAULT*/)
	: CDrawable3DBase(primitiveTopology)
	, m_bufferUsage(bufferUsage)
{
    CEngine* pEngine = CEngine::GetInstance();
    ID3D11Device& rDevice = pEngine->GetRenderer().GetDevice();
    HWND hwnd = pEngine->GetHWND();
    m_shader.Init(rDevice, hwnd);
}

bool CColorDrawableBase::InitDrawable(ID3D11Device& rDevice)
{
	if (m_indexes.size() == 0)
	{
		return false;
	}

	m_iStride = sizeof(ColorShaderDataStructures::sVertexShader);
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexBufferDesc.Usage = m_bufferUsage;
	vertexBufferDesc.ByteWidth = sizeof(ColorShaderDataStructures::sVertexShader) * (unsigned int)m_vertexes.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = m_iStride;

	vertexData.pSysMem = &m_vertexes[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	indexBufferDesc.Usage = m_bufferUsage;
	indexBufferDesc.ByteWidth = sizeof(unsigned short) * (unsigned int)m_indexes.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = m_iStride;

	indexData.pSysMem = &m_indexes[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	m_indexesFormat = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;

	const bool bResult = GenerateBuffersGetIfSucceeded(vertexBufferDesc, vertexData, indexBufferDesc, indexData, rDevice);
	m_vertexes.clear();
	m_indexes.clear();
	return bResult;
}

void CColorDrawableBase::AddVertex(const float fSidePos, const float fForwardPos, const float fUpPos, const Color color)
{
	AddVertex(Vector3(fSidePos, fUpPos, fForwardPos), color);
}

void CColorDrawableBase::AddVertex(const Vector3& rPos, const Color color)
{
	m_vertexes.push_back(ColorShaderDataStructures::sVertexShader());
	const unsigned short iNewIndex = (unsigned short)m_vertexes.size() - 1;

	ColorShaderDataStructures::sVertexShader& rNewVertexShader = m_vertexes[iNewIndex];

	rNewVertexShader.position = rPos;

	XMStoreFloat4(&rNewVertexShader.color, color);
}