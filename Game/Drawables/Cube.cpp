#include "Game/Drawables/Cube.h"

#include "Game/Scenes/Grid.h"
#include "Game/Shaders/ColorDataStructure.h"

using namespace DirectX::SimpleMath;

CCube::CCube()
	: CColorDrawableBase(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

void CCube::InitList(const std::vector<int>& rIndexes, const CGrid& rGrid, const Color color)
{
	if (rIndexes.size() == 0)
	{
		return;
	}

	m_vertexes.reserve(rIndexes.size() * 4);
	m_indexes.reserve(rIndexes.size() * 6);

	int iX, iY;
	for (const int iIndex : rIndexes)
	{
		rGrid.GetCellXYFromIndex(iIndex, iX, iY);
		InitCube(iX, iY, rGrid.GetCellSize(), color);
	}

	m_iIndexCount = static_cast<int>(m_indexes.size());

	Init();
}

void CCube::InitCube(const int iStartX, const int iStartY, const float fCellSize, const Color color)
{
	const float fStartX = iStartX * fCellSize;
	const float fStartY = iStartY * fCellSize;
	const unsigned short iStartIndex = static_cast<unsigned short>(m_vertexes.size());

	//front
	AddVertex(fStartX, fStartY, 0.f, color); //bottom left
	AddVertex(fStartX, fStartY, fCellSize, color); //up left
	AddVertex(fStartX + fCellSize, fStartY, fCellSize, color); //up right
	AddVertex(fStartX + fCellSize, fStartY, 0.f, color); //bottom right

	//back
	AddVertex(fStartX, fStartY + fCellSize, 0.f, color); //bottom left
	AddVertex(fStartX, fStartY + fCellSize, fCellSize, color); //bottom right
	AddVertex(fStartX + fCellSize, fStartY + fCellSize, fCellSize, color); //up right
	AddVertex(fStartX + fCellSize, fStartY + fCellSize, 0.f, color); //up left

	//front
	m_indexes.push_back(iStartIndex);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 2);
	m_indexes.push_back(iStartIndex);
	m_indexes.push_back(iStartIndex + 2);
	m_indexes.push_back(iStartIndex + 3);

	//back
	m_indexes.push_back(iStartIndex + 6);
	m_indexes.push_back(iStartIndex + 5);
	m_indexes.push_back(iStartIndex + 4);
	m_indexes.push_back(iStartIndex + 4);
	m_indexes.push_back(iStartIndex + 7);
	m_indexes.push_back(iStartIndex + 6);

	//left
	m_indexes.push_back(iStartIndex + 4);
	m_indexes.push_back(iStartIndex + 5);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 4);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 0);

	//right
	m_indexes.push_back(iStartIndex + 3);
	m_indexes.push_back(iStartIndex + 2);
	m_indexes.push_back(iStartIndex + 6);
	m_indexes.push_back(iStartIndex + 3);
	m_indexes.push_back(iStartIndex + 6);
	m_indexes.push_back(iStartIndex + 7);

	//top
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 5);
	m_indexes.push_back(iStartIndex + 6);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 6);
	m_indexes.push_back(iStartIndex + 2);

	//bottom
	m_indexes.push_back(iStartIndex + 4);
	m_indexes.push_back(iStartIndex + 0);
	m_indexes.push_back(iStartIndex + 3);
	m_indexes.push_back(iStartIndex + 4);
	m_indexes.push_back(iStartIndex + 3);
	m_indexes.push_back(iStartIndex + 7);

	m_iIndexCount = static_cast<int>(m_indexes.size());
}



