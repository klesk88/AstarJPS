#pragma once

//framework
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Engine/Drawables/Drawable3DBase.h"

//game
#include "Game/Shaders/ColorDataStructure.h"
#include "Game/Shaders/ColorShader.h"

//std
#include <vector>

class CColorDrawableBase : public CDrawable3DBase
{
public:
	explicit CColorDrawableBase(const D3D_PRIMITIVE_TOPOLOGY primitiveTopology, const D3D11_USAGE bufferUsage = D3D11_USAGE::D3D11_USAGE_DEFAULT);
	~CColorDrawableBase() = default;

	[[nodiscard]] bool HasElementsToStoreInBuffer() const;

protected:
	//CDrawable3DBase
	[[nodiscard]] bool InitDrawable(ID3D11Device& rDevice) override;
	[[nodiscard]] const CShaderBase& GetShader() const override;
	//CDrawable3DBase

	void AddVertex(const float fSidePos, const float fForwardPos, const float fUpPos, const DirectX::SimpleMath::Color color);
	void AddVertex(const DirectX::SimpleMath::Vector3& rPos, const DirectX::SimpleMath::Color color);

protected:
	std::vector<ColorShaderDataStructures::sVertexShader> m_vertexes;
	std::vector<unsigned short> m_indexes;
	D3D11_USAGE m_bufferUsage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

private:
	CColorShader m_shader;
};

inline bool CColorDrawableBase::HasElementsToStoreInBuffer() const { return m_indexes.size() != 0; }
inline const CShaderBase& CColorDrawableBase::GetShader() const { return m_shader; }