#pragma once

//base class extended by all drawables object which contains the main methods shared between them
//as well as it make sure that the object remove itselfs from the renderer update list before
//getting destroied

#include <d3d11.h>
#include <D3Dcommon.h>
#include <vector>

#include "../Core/SimpleMath.h"
#include "../../Utils/ClassMacros.h"

class CShaderBase;

class CDrawable3DBase
{
	NON_COPYABLE_CLASS(CDrawable3DBase)

public:
	CDrawable3DBase();
	virtual ~CDrawable3DBase();

	bool Init(const bool bAddToRenderUpdate = true);

	void Reset();
	void Clear();

	void RemoveFromRenderUpdate();
	void AddToRenderUpdateIfNeeded();
	void MarkAsNotInsideRenderUpdate();

	bool HasValidBuffer() const { return m_pVertexBuffer != nullptr; }
	bool IsInsideRenderUpdate() const { return m_bIsInsideRenderUpdate; }

	void Render(const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const;

protected:
	virtual bool InitDrawable(ID3D11Device& rDevice) = 0;
	virtual const CShaderBase& GetShader() const = 0;

	bool GenerateBuffersGetIfSucceeded(const D3D11_BUFFER_DESC& rVertexBuffer, const D3D11_SUBRESOURCE_DATA& rVertexData, const D3D11_BUFFER_DESC& rIndexBuffer, const D3D11_SUBRESOURCE_DATA& rIndexData, ID3D11Device& rDevice);

protected:
	unsigned int m_iStride;
	unsigned int m_iStartOffset;
	int m_iIndexCount;
	D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology;
	DXGI_FORMAT m_indexesFormat;

private:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	bool m_bIsInsideRenderUpdate : 1;
};