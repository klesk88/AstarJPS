#include "Square.h"

#include "../Scenes/Grid.h"
#include "../Shaders/ColorDataStructure.h"

using namespace DirectX::SimpleMath;

CSquare::CSquare()
{
	m_primitiveTopology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void CSquare::InitList(const std::vector<int>& rIndexes, const CGrid& rGrid, const Color color, const float fUpOffset)
{
	Reset();

	if (rIndexes.size() == 0)
	{
		return;
	}

	m_vertexes.reserve((int)rIndexes.size() * 4);
	m_indexes.reserve((int)rIndexes.size() * 6);

	int iX, iY;
	for (const int iIndex : rIndexes)
	{
		rGrid.GetCellXYFromIndex(iIndex, iX, iY);
		AddSquare(iX, iY, rGrid.GetCellSize(), color, fUpOffset);
	}

	m_iIndexCount = (int)m_indexes.size();

	Init();
}

void CSquare::AddSingleSquare(const int iStartX, const int iStartY, const float fCellSize, const Color& color)
{
	AddSquare(iStartX, iStartY, fCellSize, color, 0.1f);
	m_iIndexCount = (int)m_indexes.size();
}

void CSquare::AddSquare(const int iStartX, const int iStartY, const float fCellSize, const Color color, const float fUpOffset)
{
	const float fStartX = iStartX * fCellSize;
	const float fStartY = iStartY * fCellSize;
	const int iStartIndex = (int)m_vertexes.size();

	AddVertex(fStartX, fStartY, fUpOffset, color);
	AddVertex(fStartX, fStartY + fCellSize, fUpOffset, color);
	AddVertex(fStartX + fCellSize, fStartY + fCellSize, fUpOffset, color);
	AddVertex(fStartX + fCellSize, fStartY, fUpOffset, color);

	m_indexes.push_back(iStartIndex);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 3);

	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 2);
	m_indexes.push_back(iStartIndex + 3);
}

