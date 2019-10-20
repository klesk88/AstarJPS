#pragma once

#include <vector>

#include "../Shaders/ColorDataStructure.h"
#include "../Shaders/ColorShader.h"
#include "../../Framework/Engine/Core/SimpleMath.h"
#include "../../Framework/Engine/Drawables/Drawable3DBase.h"

class CColorDrawableBase : public CDrawable3DBase
{
public:
	CColorDrawableBase();
	bool HasElementsToStoreInBuffer() const { return m_indexes.size() != 0; }

protected:
	bool InitDrawable(ID3D11Device& rDevice) override;
	const CShaderBase& GetShader() const override { return m_shader; }
	void AddVertex(const float fSidePos, const float fForwardPos, const float fUpPos, const DirectX::SimpleMath::Color color);
	void AddVertex(const DirectX::SimpleMath::Vector3& rPos, const DirectX::SimpleMath::Color color);

protected:
	std::vector<ColorShaderDataStructures::sVertexShader> m_vertexes;
	std::vector<unsigned short> m_indexes;
	D3D11_USAGE m_bufferUsage;

private:
	CColorShader m_shader;
};