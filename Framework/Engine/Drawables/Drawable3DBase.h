#pragma once

#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//directx
#include <d3d11.h>
#include <D3Dcommon.h>

//std
#include <vector>

class CShaderBase;

//base class extended by all drawables object which contains the main methods shared between them
//as well as it make sure that the object remove itself from the renderer update list before
//getting destroyed
class CDrawable3DBase
{
	NON_COPYABLE_CLASS(CDrawable3DBase)

public:
	explicit CDrawable3DBase(const D3D_PRIMITIVE_TOPOLOGY primitiveTopology);
	virtual ~CDrawable3DBase();

	void Init();

	void Reset();

	void RemoveFromRenderUpdate();
	void AddToRenderUpdateIfNeeded();
	void MarkAsNotInsideRenderUpdate();

	[[nodiscard]] bool HasValidBuffer() const;
	[[nodiscard]] bool IsInsideRenderUpdate() const;

	void Render(const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const;

protected:
	[[nodiscard]] virtual bool InitDrawable(ID3D11Device& rDevice) = 0;
	[[nodiscard]] virtual const CShaderBase& GetShader() const = 0;

	[[nodiscard]] bool GenerateBuffersGetIfSucceeded(const D3D11_BUFFER_DESC& rVertexBuffer, const D3D11_SUBRESOURCE_DATA& rVertexData, const D3D11_BUFFER_DESC& rIndexBuffer, const D3D11_SUBRESOURCE_DATA& rIndexData, ID3D11Device& rDevice);

private:
	void Clear();

protected:
	unsigned int m_iStride = 0;
	unsigned int m_iStartOffset = 0;
	int m_iIndexCount = 0;
	D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED;
	DXGI_FORMAT m_indexesFormat = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

private:
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	bool m_bIsInsideRenderUpdate = false;
};

inline bool CDrawable3DBase::HasValidBuffer() const { return m_pVertexBuffer != nullptr; }
inline bool CDrawable3DBase::IsInsideRenderUpdate() const { return m_bIsInsideRenderUpdate; }