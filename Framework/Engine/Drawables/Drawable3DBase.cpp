#include "Drawable3DBase.h"

#include "../Engine.h"
#include "../Render/Renderer.h"
#include "../Shaders/ShaderBase.h"
#include "../../Utils/DebugMacros.h"

using namespace DirectX::SimpleMath;

CDrawable3DBase::CDrawable3DBase()
	: m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_iStride(0)
	, m_iStartOffset(0)
	, m_iIndexCount(0)
	, m_primitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED)
	, m_indexesFormat(DXGI_FORMAT::DXGI_FORMAT_R32_UINT)
	, m_bIsInsideRenderUpdate(false)
{}

CDrawable3DBase::~CDrawable3DBase()
{
	Clear();
}

void CDrawable3DBase::Reset()
{
	Clear();
	RemoveFromRenderUpdate();
}

void CDrawable3DBase::Clear()
{
	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	m_iStride = 0;
	m_iStartOffset = 0;
	m_iIndexCount = 0;
}

void CDrawable3DBase::AddToRenderUpdateIfNeeded()
{
	if (m_bIsInsideRenderUpdate) 
	{
		return;
	}

	CEngine::GetInstance()->GetRenderer().AddDrawable(*this);
	m_bIsInsideRenderUpdate = true;
}

void CDrawable3DBase::RemoveFromRenderUpdate()
{
	if (!m_bIsInsideRenderUpdate)
	{
		return;
	}

	CEngine::GetInstance()->GetRenderer().RemoveDrawable(*this);
	m_bIsInsideRenderUpdate = false;
}

bool CDrawable3DBase::Init(const bool bAddToRenderUpdate)
{
	ID3D11Device& rDevice = CEngine::GetInstance()->GetRenderer().GetDevice();
	
	if (!InitDrawable(rDevice))
	{
		RemoveFromRenderUpdate();
		return false;
	}

	if (bAddToRenderUpdate)
	{
		AddToRenderUpdateIfNeeded();
	}

	return true;
}

bool CDrawable3DBase::GenerateBuffersGetIfSucceeded(const D3D11_BUFFER_DESC& rVertexBuffer, const D3D11_SUBRESOURCE_DATA& rVertexData, const D3D11_BUFFER_DESC& rIndexBuffer, const D3D11_SUBRESOURCE_DATA& rIndexData, ID3D11Device& rDevice)
{
	HRESULT result = rDevice.CreateBuffer(&rVertexBuffer, &rVertexData, &m_pVertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	result = rDevice.CreateBuffer(&rIndexBuffer, &rIndexData, &m_pIndexBuffer);
	if (FAILED(result))
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
		return false;
	}

	return true;
}

void CDrawable3DBase::Render(const Matrix& rViewMatrix, const Matrix& rWorldMatrix, const Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const
{
	ASSERT(m_primitiveTopology != D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED);
	ASSERT(m_iStride != 0);
	ASSERT(m_pVertexBuffer != nullptr);
	ASSERT(m_pIndexBuffer != nullptr);

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	rDeviceContext.IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_iStride, &m_iStartOffset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	rDeviceContext.IASetIndexBuffer(m_pIndexBuffer, m_indexesFormat, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	rDeviceContext.IASetPrimitiveTopology(m_primitiveTopology);

	GetShader().Render(m_iIndexCount, rWorldMatrix, rViewMatrix, rProjMatrix, rDeviceContext);
}
