#include "Game/Drawables/Line.h"

#include "Game/Scenes/Grid.h"
#include "Game/Shaders/ColorDataStructure.h"

using namespace DirectX::SimpleMath;

CLine::CLine()
	: CColorDrawableBase(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST)
{
}

void CLine::AddLine(const Vector3& rStartPos, const Vector3& rEndPos, const Color color)
{
	AddVertex(rStartPos, color);
	AddVertex(rEndPos, Color(DirectX::Colors::Yellow));

	m_indexes.push_back(0);
	m_indexes.push_back(1);
	m_iIndexCount = static_cast<int>(m_indexes.size());
}
