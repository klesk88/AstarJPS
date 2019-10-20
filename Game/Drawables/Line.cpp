#include "Line.h"

#include "Cube.h"

#include "../Scenes/Grid.h"
#include "../Shaders/ColorDataStructure.h"

using namespace DirectX::SimpleMath;

CLine::CLine()
{
	m_primitiveTopology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
}

void CLine::AddLine(const Vector3& rStartPos, const Vector3& rEndPos, const Color color)
{
	AddVertex(rStartPos, color);
	AddVertex(rEndPos, Color(DirectX::Colors::Yellow));

	m_indexes.push_back(0);
	m_indexes.push_back(1);
	m_iIndexCount = (int)m_indexes.size();
}
